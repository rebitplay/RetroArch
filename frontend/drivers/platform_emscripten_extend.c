#include <emscripten/emscripten.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Extension for RetroArch Emscripten Platform
 * Exported via EMSCRIPTEN_KEEPALIVE to avoid Makefile modifications.
 */

EMSCRIPTEN_KEEPALIVE
void cmd_set_fastforward_ratio(float ratio)
{
   settings_t *settings = config_get_ptr();
   configuration_set_float(settings, settings->floats.fastforward_ratio, ratio);
   command_event(CMD_EVENT_SET_FRAME_LIMIT, NULL);
}

#ifdef __cplusplus
}
#endif
