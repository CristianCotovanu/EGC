#pragma once

#include <Core/Engine.h>
#include <BowAndArrow/Entities/Arrow.h>
#include <BowAndArrow/Entities/Bow.h>
#include <BowAndArrow/Entities/Balloon.h>
#include <BowAndArrow/Entities/Shuriken.h>

namespace CollisionManager {
	GLboolean CollideBowShuriken(Bow* bow, Shuriken* shuriken);
	GLboolean CollideArrowBalloon(Arrow* arrow, Balloon* balloon);
	GLboolean CollideArrowShuriken(Arrow* arrow, Shuriken* shuriken);
}