#include "IDisplayServiceInterface.h"
#include "Log.h"

using namespace CLASSICDIY;

class FakeOled : public IDisplayServiceInterface {
 public:
   void Display(const char *hdr1, const char *detail1, const char *hdr2, const char *detail2) {
      logd("Display Line1: %s %s ", hdr1, detail1);
      logd("Display Line2: %s %s ", hdr2, detail2);
   }
   void Display(const char *hdr1, const char *detail1, const char *hdr2, int count) {
      logd("Display Line1: %s %s ", hdr1, detail1);
      logd("Display Line2: %s %d ", hdr2, count);
   }
};