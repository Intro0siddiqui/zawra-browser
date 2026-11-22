//! Zawra Shield native adblock module.

pub mod engine;

pub use engine::{
    normalize_domain, ShieldDecision, ShieldStats, ZawraShield,
    DEFAULT_FILTER_RULES, ESTIMATED_BYTES_PER_BLOCKED_REQUEST,
};
