#include "tests/Test.h"
#include "ImGui/imgui.h"


namespace test {
	
	
	TestMenu::TestMenu(Test*& currentTestPointer)
		: m_CurrentTest(currentTestPointer)
	{
	}

	void test::TestMenu::OnImGuiRender()
	{
		for (auto& test : m_Test) 
		{
			if(ImGui::Button(test.first.c_str())) 
			{
				m_CurrentTest = test.second();
			}
		}
	}
}
