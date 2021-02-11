#include <string>

#include <include/glm.h>

#include <BowAndArrow/Helpers/CollisionManager.h>
#include <BowAndArrow\Constants\Constants.cpp>

GLboolean CollisionManager::CollideBowShuriken(Bow* bow, Shuriken* shuriken) {
	GLfloat dx = bow->getX() - shuriken->getX();
	GLfloat dy = bow->getY() - shuriken->getY();
	GLfloat distance = sqrt(dx * dx + dy * dy);
	return distance < bow->getRadius() + shuriken->getRadius();
}

GLboolean CollideArrowWith(Arrow* arrow, GLfloat colliderX, GLfloat colliderY, GLfloat colliderRadius) {
	GLfloat dx = arrow->getX() - colliderX;
	GLfloat dy = arrow->getY() - colliderY;
	GLfloat distance = sqrt(dx * dx + dy * dy);

	return distance - ArrowConstants::width / 2 <= colliderRadius;
}

GLboolean CollisionManager::CollideArrowBalloon(Arrow* arrow, Balloon* balloon) {
	return CollideArrowWith(arrow, balloon->getX(), balloon->getY(), balloon->getRadius());
}

GLboolean CollisionManager::CollideArrowShuriken(Arrow* arrow, Shuriken* shuriken) {
	return CollideArrowWith(arrow, shuriken->getX(), shuriken->getY(), shuriken->getRadius());
}
