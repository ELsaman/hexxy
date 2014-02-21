// MovementSequence.h

#ifndef _MOVEMENTSEQUENCE_h
#define _MOVEMENTSEQUENCE_h


#include "Defines.h"

#include "Movement.h"
#include <utility.h>
#include <unwind-cxx.h>
#include <system_configuration.h>
#include <StandardCplusplus.h>
#include <vector>
#include <deque>

//
//
struct MovementSequence
{
    MovementSequence(bool inversed, bool infinite = false);
    virtual ~MovementSequence() {}

    virtual void Init();

    bool HasSequence(uint8_t index) { return !(movement[index].empty()); }
    const Movement * GetNextSequence(uint8_t index) const { return &movement[index].front(); }
    void ClearTop(uint8_t index) { movement[index].pop_front(); }
    bool IsInfinite() const { return _infinite; }

private:
    bool _infinite;

protected:
    std::deque<Movement> movement[TOTAL_SEGMENTS];
    bool _inversed;

};

#endif

