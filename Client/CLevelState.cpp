#include "pch.h"
#include "CLevelState.h"


#include "CLevelStateIdle.h"
#include "CLevelStateIn.h"
#include "CLevelStateOut.h"
#include "CLevelChange.h"

CLevelStateIdle CLevelState::Idle;
CLevelStateIn CLevelState::In;
CLevelStateOut CLevelState::Out;
CLevelChange CLevelState::Change;