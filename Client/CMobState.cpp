#include "pch.h"
#include "CMobState.h"

#include "CMobIdleLeft.h"
#include "CMobIdleRight.h"
#include "CMobDead.h"
#include "CMobAlert.h"
#include "CMobDamaged.h"
#include "CMobSpawn.h"
#include "CMobWalkRight.h"
#include "CMobWalkLeft.h"

CMobIdleLeft CMobState::idleleft;
CMobIdleRight CMobState::idleright;
CMobDead CMobState::dead;
CMobAlert CMobState::alert;
CMobDamaged CMobState::damaged;
CMobSpawn CMobState::spawn;
CMobWalkRight CMobState::walkright;
CMobWalkLeft CMobState::walkleft;