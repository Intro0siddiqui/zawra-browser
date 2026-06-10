# Heap Corruption Leak: Navigation Timer CallableWrapper

## Background
During shutdown, `Navigation::~Navigation()` → `ProcessThrottlerTimedActivity::~ProcessThrottlerTimedActivity()`
→ `RunLoop::Timer::~Timer()` → `Function<void()>` destruction → `delete` on a corrupted `CallableWrapper`.

The fix (placement-new over the timer with an empty function) leaks the corrupted wrapper
instead of crashing on `delete`. This documents the leak and hypotheses for a root-cause fix.

## Leak Details
- **Size:** ~48 bytes per browser session (one CallableWrapper allocation)
- **When:** Single leak during initial process swap (dummy → real WebProcess)
- **Impact:** Negligible — browser runs indefinitely with no memory growth from this

## Root-Cause Investigation (Deferred)

### Known Facts
1. Memory is already corrupted BEFORE `clearAllNavigations()` runs
2. Corruption happens during the process swap (`didFinishLaunching` path)
3. It's a use-after-free or wild write to the CallableWrapper's heap memory
4. The corrupted pointer lives in `ProcessThrottlerTimedActivity::m_timer::m_function::m_callableWrapper`
5. This is inside `API::Navigation::m_clientNavigationActivity`, created during page load

### Hypotheses to Test

**H1 — Reorder cleanup** (TESTED - FAILED)
Move `resetStateAfterProcessTermination()` before `disconnectProcess()`.
Memory was already corrupted before either ran.

**H2 — Null timer in dtor** (TESTED - WORKAROUND APPLIED)
placement-new an empty timer over the corrupted one. Leaks the wrapper.

**H3 — Investigate process swap**
The real `WebProcessProxy::didFinishLaunching` with a valid connection sets up
IPC, sends messages, and may trigger code that frees/reuses the Navigation's
CallableWrapper memory. Add logging to track when the CallableWrapper is allocated
and when it gets corrupted.

**H4 — Guard in `Navigation` or `WebNavigationState`**
Explicitly clear `m_clientNavigationActivity` in `Navigation` destructor before
implicit member destruction. (Requires `ProcessThrottlerTimedActivity` to support
move-assignment or reset.)

**H5 — Avoid `std::bind` in `ProcessThrottlerTimedActivity`**
Use empty/noop callback `[]{}` instead of `std::bind(f, this)`. Would break
navigation timeout functionality — only viable if timeout is unused in Zawra.

### Current Status
- Fix applied: `patches/webkit/Source/WebKit/UIProcess/ProcessThrottler.h`
- ~48 bytes leaked once per session
- Browser runs stably headless and headful
- Root cause investigation deferred
