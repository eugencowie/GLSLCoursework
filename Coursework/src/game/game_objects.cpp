#include "game_objects.hpp"

void Car::update(int elapsedTime)
{
	if (turned)
	{
		transform.move({0, 0, -0.005f * elapsedTime});
	}
	else
	{
		transform.move({0.005f * elapsedTime, 0, 0});
	}

	if (!turned && transform.position().x > 7)
	{
		turned = true;
		transform.move({5, 0.05f, 0});
		transform.rotations({{90}});
		for (Carlight& light : lights)
		{
			light.pointLightOffset = vec3(-light.pointLightOffset.z, light.pointLightOffset.y, -light.pointLightOffset.x);
			light.spotLightOffset = vec3(-light.spotLightOffset.z, light.spotLightOffset.y, -light.spotLightOffset.x);
			light.spotLight->direction = vec3(-light.spotLight->direction.z, light.spotLight->direction.y, -light.spotLight->direction.x);
		}
	}
	else if (turned && transform.position().z < -20)
	{
		turned = false;
		transform.position({-20.f, 0.05f, -2});
		transform.rotations({});
		for (Carlight& light : lights)
		{
			light.pointLightOffset = vec3(-light.pointLightOffset.z, light.pointLightOffset.y, -light.pointLightOffset.x);
			light.spotLightOffset = vec3(-light.spotLightOffset.z, light.spotLightOffset.y, -light.spotLightOffset.x);
			light.spotLight->direction = vec3(-light.spotLight->direction.z, light.spotLight->direction.y, -light.spotLight->direction.x);
		}
	}

	for (Carlight& light : lights)
	{
		light.update();
	}
}
