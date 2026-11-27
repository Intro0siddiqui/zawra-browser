//! Zawra Sieve (formerly Zawra Shield) native adblock and scriptlet engine.

pub mod engine;

pub use engine::{
    builtin_resources, normalize_domain, resolve_filters_dir, CosmeticResources, ShieldDecision,
    ShieldStats, ZawraShield, ZawraSieve, Zawra_Sieve_CheckRequest, Zawra_Sieve_FreeString,
    Zawra_Sieve_GetCosmeticCss, Zawra_Sieve_GetInjectedScript, DEFAULT_FILTER_RULES,
    ESTIMATED_BYTES_PER_BLOCKED_REQUEST,
};
