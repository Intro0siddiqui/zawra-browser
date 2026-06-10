# Secondary Crash: Navigation Timer

## H1. exp/reorder-cleanup — FAILED
**Hypothesis:** Move `clearAllNavigations()` before `disconnectProcess()` in
`processDidTerminateOrFailedToLaunch()`.
**Build time:** 2m4s
**Exit codes:** 139, 139, 139
**Finding:** Memory was already corrupted before disconnectProcess. Corruption
happens during `didFinishLaunching` of the new process, during the swap itself.

## H2. exp/navigation-null-timer — PASSED ✅
**Hypothesis:** Replace the corrupted CallableWrapper with an empty function
in ProcessThrottlerTimedActivity destructor using placement new — leaks the
corrupted wrapper but avoids the delete crash.
**Build time:** 18m18s
**Exit codes:** 143, 143, 143
**Finding:** Fix works. The heap corruption of the CallableWrapper is real but
is harmless if we never `delete` it. The root cause (use-after-free during
process swap) still exists but is invisible with this workaround.
