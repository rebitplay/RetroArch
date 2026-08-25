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

EMSCRIPTEN_KEEPALIVE
char *rebit_save_state_info(void)
{
   size_t state_size = 0;
   void *state       = content_export_state(&state_size);
   char *info        = (char*)malloc(64);

   if (!info)
   {
      free(state);
      return NULL;
   }

   if (!state)
      snprintf(info, 64, "Could not serialize state|0|0");
   else
      snprintf(info, 64, "%zu|%zu|1", state_size, (size_t)state);

   return info;
}

EMSCRIPTEN_KEEPALIVE
bool rebit_load_state(const void *state, size_t state_size)
{
   return state && state_size > 0 && content_deserialize_state(state, state_size);
}

#ifdef __cplusplus
}
#endif
