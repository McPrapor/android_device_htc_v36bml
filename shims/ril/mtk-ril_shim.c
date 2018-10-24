#include <log/log.h>
#include <cutils/log.h>

#define SHIMDEBUG 1

void (*real_switchStkUtkModeByCardType)(RIL_SOCKET_ID rid) = NULL;
static void (*real_handleCardTypeUrc)(const char *s, RIL_SOCKET_ID rid) = NULL;
extern void (*real_RIL_requestProxyTimedCallback) (RIL_TimedCallback callback, void *param, const struct timeval *relativeTime, int proxyId) = NULL;

void __attribute__((constructor)) initialize(void) {
  real_switchStkUtkModeByCardType = dlsym(RTLD_NEXT, "switchStkUtkModeByCardType");
  if (real_switchStkUtkModeByCardType == NULL) {
#ifdef SHIMDEBUG
    RLOGD("SHIM real_switchStkUtkModeByCardType not found");
#endif
  }
  real_handleCardTypeUrc = dlsym(RTLD_NEXT, "handleCardTypeUrc");
  if (real_handleCardTypeUrc == NULL) {
#ifdef SHIMDEBUG    
    RLOGD("SHIM real_handleCardTypeUrc not found");
#endif    
  }
  real_RIL_requestProxyTimedCallback = dlsym(RTLD_NEXT, "real_RIL_requestProxyTimedCallback");
  if (real_RIL_requestProxyTimedCallback == NULL) {
#ifdef SHIMDEBUG    
    RLOGD("SHIM real_RIL_requestProxyTimedCallback not found");
#endif    
  }
}

void switchStkUtkModeByCardType(RIL_SOCKET_ID rid) {
#ifdef SHIMDEBUG      
    RLOGD("SHIM switchStkUtkModeByCardType call rid: %d", rid);
#endif
    if (real_switchStkUtkModeByCardType == NULL) {
#ifdef SHIMDEBUG          
      RLOGD("SHIM real_switchStkUtkModeByCardType found, calling...");
#endif      
      return real_switchStkUtkModeByCardType(rid);
    }
}

static void handleCardTypeUrc(const char *s, RIL_SOCKET_ID rid) {
#ifdef SHIMDEBUG    
    RLOGD("SHIM handleCardTypeUrc call rid: %d", rid);
#endif
    if (real_handleCardTypeUrc != NULL) {
#ifdef SHIMDEBUG          
        RLOGD("SHIM real_handleCardTypeUrc found, calling...");
#endif      
        return real_handleCardTypeUrc(s, rid);
    }
}

void RIL_requestProxyTimedCallback (RIL_TimedCallback callback, 
                                     void *param, const struct timeval *relativeTime, int proxyId) {
#ifdef SHIMDEBUG    
    RLOGD("SHIM RIL_requestProxyTimedCallback call rid: %d", rid);
#endif
    if (real_RIL_requestProxyTimedCallback != NULL) {
#ifdef SHIMDEBUG          
        RLOGD("SHIM real_RIL_requestProxyTimedCallback found, calling...");
#endif      
        return real_RIL_requestProxyTimedCallback(callback, param, relativeTime, proxyId);
    }  
}

