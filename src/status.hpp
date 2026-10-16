// State shared between the fix and its status file (status_report.cpp).
#pragma once
#include <cstdint>
#include <string>

namespace glass {
// Experimental fixes ([experimental] in the settings file).
struct Experimental {
    int detail_clamp = 0, edge_fade = 0, angle_softening = 0, edge_stretch = 0; // percent / hundredths of a render pixel
    int dark_screens = 0; // dark screen fix on/off
    int seam_fix = 1; // UV seam fix on/off (on by default)
    bool operator==(const Experimental&) const = default;
};

struct Status {
    std::string gpu, driver, dlss_version, fsr_version;
    bool gpu_known = false, nvidia = false, dlss_loaded = false, fsr_loaded = false, shader_found = false;
    bool enabled = false, tint = false, jitter_positive = false, active = false, extra_smoothing = false;
    Experimental experimental;
    int line_smoothing = 0, glass_strength = 100;
    uint64_t dlss_calls = 0, dlss_upscales = 0, fsr_calls = 0, screen_draws = 0, recorded = 0, overlay_frames = 0, skipped = 0;
    unsigned screens = 0, render_w = 0, render_h = 0, out_w = 0, out_h = 0;
    const char* upscaler = "DLSS"; // the one the fix was last drawn after
    const char* problem = nullptr; // plain-language description of the current problem, if any
    std::wstring log_path;
    std::string capture; // screen capture progress / result
};
Status status();
void set_enabled(bool on);
void set_tint(bool on);
void request_capture();

// The text of glass-cockpit-dlss-fix-status.txt: summary, checks, settings and a report for bug reports.
std::string status_text(const Status& s);
}
