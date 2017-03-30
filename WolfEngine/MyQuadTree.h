 #ifndef MYQUADTREE_H
#define MYQUADTREE_H

#include "Math.h"
#include "Globals.h"
#include <vector>

#define BUCKET_SPACE 1

class GameObject;

struct QuadNode 
{
	~QuadNode()
	{
		if (children != nullptr)
		{
			for (int i = 0; i < 4; ++i)
				RELEASE(children[i]);
		}
		RELEASE_ARRAY(children);
		RELEASE_ARRAY(bucket);
	}

	AABB limit;
	
	GameObject** bucket;
	unsigned int bucket_size = 0;

	QuadNode** children = nullptr;
};

class MyQuadTree
{
public:
	MyQuadTree(AABB limits);
	~MyQuadTree();

	void Draw();
	void Insert(GameObject* game_object);
	void IntersectCandidates(std::vector<GameObject*>& candidates, AABB primitive);

private:
	QuadNode* root = nullptr;
};
#endif // !MODEL_H

