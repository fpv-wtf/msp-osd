#include "parson.h"
#define JSON_CONFIG_PATH "/opt/etc/package-config/msp-osd/config.json"
static JSON_Object *root_object = NULL;
static void load_config() {
   JSON_Value *root_value = NULL;
    if(root_object == NULL) {
        root_value = json_parse_file(JSON_CONFIG_PATH);
        if (json_value_get_type(root_value) != JSONObject) {
            return;
        }
        root_object = json_value_get_object(root_value);
    }
}

int get_boolean_config_value(const char* key) {
    load_config();
    if (root_object != NULL) {
        // parson returns -1 for undefined keys, which can happen when
        // new keys are defined in the schema - ensure they come back as false
        return json_object_get_boolean(root_object, key) > 0;
    } else {
        return 0;
    }
}