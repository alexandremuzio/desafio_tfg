#include "stdafx.h"
#include "CppUnitTest.h"
#include "Vector2.h"
#include "GameObject.h"
#include "DodgeLaserMovement.h"
#include "MathUtils.h"
#include <sstream>
#include <CppUnitTestLogger.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TFGBotTest
{
	TEST_CLASS(DodgeTest)
	{
	public:
		
		TEST_METHOD(TestGetP)
		{
			float d2r = MathUtils::deg2rad;
			DodgeLaserMovement* dm = new DodgeLaserMovement();

			GameObject* go = new GameObject(0, 0, 0, -1, -1, 10.0f);
			Assert::AreEqual(true, Vector2::VecEqual(Vector2(-10/sqrt(2), 10/sqrt(2)), dm->GetP0(go), 0.001f));

			/*Vector2 v = dm->GetP1(go);
			stringstream ss;
			ss << v.x << " " << v.y << endl;
			Logger::WriteMessage(ss.str().c_str());*/

			Assert::AreEqual(true, Vector2::VecEqual(Vector2(10 / sqrt(2), -10 / sqrt(2)), dm->GetP1(go), 0.001f));

			go = new GameObject(0, 1, -1, sin(30 * d2r), -cos(30 * d2r), 7.0f);
			Assert::AreEqual(true, Vector2::VecEqual(Vector2(1 - 7*sin(60 * d2r), -1 - 7*cos(60 * d2r)), dm->GetP0(go), 0.001f));
			Assert::AreEqual(true, Vector2::VecEqual(Vector2(1 + 7 * cos(30 * d2r), -1 + 7 * sin(30 * d2r)), dm->GetP1(go), 0.001f));

			/*Vector2 v = dm->GetP0(go);
			stringstream ss;
			ss << v.x << " " << v.y << endl;
			Logger::WriteMessage(ss.str().c_str());*/
		}

		TEST_METHOD(TestGetDirToEscape) {
			float d2r = MathUtils::deg2rad;
			float pi = MathUtils::PI;
			DodgeLaserMovement* dm = new DodgeLaserMovement();

			GameObject* go = new GameObject(0, 0, 0, -1, -1, 10.0f);

			/*Vector2 v = dm->GetDirToEscape(go, pi/2, Vector2(-1, -0.8f));
			stringstream ss;
			ss << v.x << " " << v.y << endl;
			Logger::WriteMessage(ss.str().c_str());*/

			Assert::AreEqual(true, Vector2::VecEqual(Vector2::LEFT_UP, dm->GetDirToEscape(go, pi/2, Vector2(-1, -0.8f)), 0.001f));
			Assert::AreEqual(true, Vector2::VecEqual(Vector2::RIGHT_DOWN, dm->GetDirToEscape(go, pi/2, Vector2(-1, -1.2f)), 0.001f));
		}

		// Vector2
		TEST_METHOD(TestSetLength) {
			Vector2 v = Vector2(3, 4);

			v.SetLength(10);
			Assert::AreEqual(true, Vector2::VecEqual(v, Vector2(6, 8), 0.001));

			v.SetLength(2.5f);
			Assert::AreEqual(true, Vector2::VecEqual(v, Vector2(1.5f, 2), 0.001));

			v = Vector2(-3, 4);

			v.SetLength(10);
			Assert::AreEqual(true, Vector2::VecEqual(v, Vector2(-6, 8), 0.001));

			v.SetLength(2.5f);
			Assert::AreEqual(true, Vector2::VecEqual(v, Vector2(-1.5f, 2), 0.001));

		}
	};
}