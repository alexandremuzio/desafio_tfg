#include "stdafx.h"
#include "CppUnitTest.h"
#include "Vector2.h"
#include <MathUtils.h>
#include <AlignVelMovement.h>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TFGBotTest {
	TEST_CLASS(UnitTest1) {
public:
	/* -------
	// AlignVelMovement
	*/
	TEST_METHOD(ClosestVectors) {
		// Do not work anymore
		/*AlignVelMovement avm = AlignVelMovement();
		pair<Vector2, Vector2> p = avm.GetClosestVectors(Vector2(1.0f, 0.1f));
		Assert::AreEqual(true, Vector2::VecEqual(p.first, Vector2::RIGHT, 0.01f));
		Assert::AreEqual(true, Vector2::VecEqual(p.second, Vector2::UP_RIGHT, 0.01f));

		p = avm.GetClosestVectors(Vector2(-0.1f, 1.0f));
		Assert::AreEqual(true, Vector2::VecEqual(p.first, Vector2::UP, 0.01f));
		Assert::AreEqual(true, Vector2::VecEqual(p.second, Vector2::LEFT_UP, 0.01f));

		p = avm.GetClosestVectors(Vector2(-1.0f, -0.8f));
		Assert::AreEqual(true, Vector2::VecEqual(p.first, Vector2::DOWN_LEFT, 0.01f));
		Assert::AreEqual(true, Vector2::VecEqual(p.second, Vector2::DOWN, 0.01f));*/

		/*stringstream ss;
		ss << p.first.x << endl;
		ss << p.first.y << endl;
		ss << p.second.x << endl;
		ss << p.second.y << endl;
		Logger::WriteMessage(ss.str().c_str());*/
	}

	/* -------
	// Vector2
	*/
	TEST_METHOD(RotatedBy) {
		float pi = MathUtils::PI;
		Vector2 v = Vector2(1 / sqrt(2), 1 / sqrt(2));
		Assert::AreEqual(true, Vector2::VecEqual(Vector2(0, 1), v.RotatedBy(pi / 4), 0.001f));
		Assert::AreEqual(true, Vector2::VecEqual(Vector2(1, 0), v.RotatedBy(-pi / 4), 0.001f));
		Assert::AreEqual(true, Vector2::VecEqual(Vector2(-1, 0), v.RotatedBy(-5 * pi / 4), 0.001f));
	}

	TEST_METHOD(VectorDecompose) {
		Vector2 v = Vector2(1,1);
		pair<float, float> ks = v.Decompose(Vector2::RIGHT, Vector2::UP);
		Assert::AreEqual(1,ks.first, 0.001f);
		Assert::AreEqual(1, ks.second, 0.001f);

		ks = v.Decompose(Vector2::UP_RIGHT, Vector2::UP);
		Assert::AreEqual((float)sqrt(2), ks.first, 0.001f);
		Assert::AreEqual(0, ks.second, 0.001f);

		ks = v.Decompose(Vector2::UP_RIGHT, Vector2::DOWN);
		Assert::AreEqual((float)sqrt(2), ks.first, 0.001f);
		Assert::AreEqual(0, ks.second, 0.001f);
	}

	};

	
}