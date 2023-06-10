
#pragma once
#include <ArduinoJson.h>

typedef struct HeFengCurrentData {

  String weather;
  String temp;
  String temp_min;
  String temp_max;
  String humidity;
  String windSpeed;
  String icon;
}
HeFengCurrentData;
typedef struct HeFengForeData {
  String datestr;
  String temp_min;
  String temp_max;
  String icon;
}
HeFengForeData;
class HeFeng {
  private:
    String getMeteoconIcon(String cond_code);
  public:
    HeFeng();
    void doUpdateCurr(HeFengCurrentData *data, String key, String lat, String lon);
    void doUpdateFore(HeFengForeData *data, String key, String lat, String lon);
};
