#include "ComponentRectTransform.h"
#include "Interface.h"
#include "GameObject.h"

ComponentRectTransform::ComponentRectTransform(GameObject * parent) : Component(Component::Type::RECT_TRANSFORM, parent)
{

}

ComponentRectTransform::~ComponentRectTransform()
{
}

void ComponentRectTransform::OnDraw() const
{
}

bool ComponentRectTransform::OnEditor()
{
	bool node_open = ImGui::CollapsingHeader("Rect Transform");

	if (node_open)
	{
		ImGui::DragFloat2("Position", pos);

		ImGui::DragFloat2("Size", size);
	}

	return ImGui::IsItemClicked();
}
