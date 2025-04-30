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
	bounds.left = other.x;
	bounds.right = other.x + other.w;
	bounds.top = other.y;
	bounds.bottom = other.y + other.h;
	return bounds;
}

Collider::CollisionBounds Collider::setCollisionBoundsSelf()
{
	CollisionBounds bounds;
	bounds.left = m_rect.x;
	bounds.right = m_rect.x + m_rect.w;
	bounds.top = m_rect.y;
	bounds.bottom = m_rect.y + m_rect.h;
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
