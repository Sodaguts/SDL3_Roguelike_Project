#include "Collider.h"

bool Collider::checkCollision(SDL_Rect other)
{
	CollisionBounds selfBounds = setCollisionBoundsSelf();
	CollisionBounds otherBounds = setCollisionBoundsOther(other);
	return compareBounds(selfBounds, otherBounds);
}

Collider::CollisionBounds Collider::setCollisionBoundsOther(SDL_Rect other)
{
	CollisionBounds bounds;
	bounds.setBounds(other);
	return bounds;
}

Collider::CollisionBounds Collider::setCollisionBoundsSelf()
{
	CollisionBounds bounds;
	bounds.setBounds(m_rect);
	return bounds;
}

bool Collider::compareBounds(CollisionBounds selfBounds, CollisionBounds otherBounds)
{
	if (selfBounds.bottom <= otherBounds.top)
	{
		return false;
	}

	if (selfBounds.top >= otherBounds.bottom)
	{
		return false;
	}

	if (selfBounds.right <= otherBounds.left)
	{
		return false;
	}

	if (selfBounds.left >= otherBounds.right)
	{
		return false;
	}
	return true;
}
