#include "pch.h"
#include "CppUnitTest.h"

#include "../AirWatcher2/AirWatcher2.cpp"
#include "../AirWatcher2/Service.cpp"
#include "../AirWatcher2/Sensor.cpp"
#include "../AirWatcher2/Cleaner.cpp"
#include "../AirWatcher2/Attribute.cpp"
#include "../AirWatcher2/Measurement.cpp"
#include "../AirWatcher2/ATMO_index.cpp"
#include "../AirWatcher2/AnalysisView.cpp"
#include "../AirWatcher2/capture_user_input.cpp"
#include "../AirWatcher2/mysql_lib.cpp"
#include "../AirWatcher2/AgenciesView.cpp"
#include "../AirWatcher2/IndividualsView.cpp"
#include "../AirWatcher2/ProvidersView.cpp"
#include "../AirWatcher2/User.cpp"
#include "../AirWatcher2/Agency.cpp"
#include "../AirWatcher2/Individual.cpp"
#include "../AirWatcher2/Provider.cpp"




using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{
	TEST_CLASS(Test)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Service s;

			ATMO_index atmo = s.calculateAirQualityIndex(44, 1, "2019-01-01 12:00:00");

			Assert::AreEqual(7, atmo.atmoIndex);
			
		}

		TEST_METHOD(TestMethod2)
		{
			Service s;

			ATMO_index atmo = s.calculateAirQualityIndex(46, 3, 100, "2019-01-01 12:00:00", "2019-05-05 12:00:00");

			Assert::AreEqual(7, atmo.atmoIndex);

		}

		TEST_METHOD(TestMethod3)
		{
			Service s;

			ATMO_index atmo = s.calculateAirQualityIndex(46, 3, 200, "2019-05-05 12:00:00");

			Assert::AreEqual(8, atmo.atmoIndex);

		}

		TEST_METHOD(TestMethod4)
		{
			Service s;

			vector<pair<float, int>> res = s.similarSensor("2019-01-05 12:00:00", "2019-11-05 12:00:00", "Sensor1");
			
			Assert::AreEqual(28, res[1].second);

		}

		TEST_METHOD(TestMethod5)
		{
			Service s;

			vector<pair<float, float>> res = s.improveCleaner("Cleaner1");

			Assert::AreEqual((float)6, res[0].second);

		}

		TEST_METHOD(TestMethod6)
		{
			Service s;

			float a = s.analyzeIndividualData("Sensor70");

			bool ok = false;
			if (a > 95) {
				ok = true;
			}

			Assert::AreEqual(true, ok);

		}

		TEST_METHOD(TestMethod7)
		{
			Service s;

			float a = s.analyzeIndividualData("Sensor36");

			bool ok = false;
			if (a > 95) {
				ok = true;
			}

			Assert::AreEqual(false, ok);

		}
	};
}
