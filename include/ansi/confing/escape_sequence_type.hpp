#pragma once

// #define DEC_ESCAPE_SEQUENCES
#define SCO_ESCAPE_SEQUENCES

#if  defined(DEC_ESCAPE_SEQUENCES) &&  defined(SCO_ESCAPE_SEQUENCES)
  #error DEFINE ONLY ONE ESCAPE SEQUENCE TYPE

#endif

#if !defined(DEC_ESCAPE_SEQUENCES) && !defined(SCO_ESCAPE_SEQUENCES)
  #error DEFINE ESCAPE SEQUENCE TYPE

#endif
