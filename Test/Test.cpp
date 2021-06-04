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
#include "../AirWatcher2/Agency.cpp"




using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{
	TEST_CLASS(Test)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			//Service s;

			Assert::AreEqual(5, 5);
			
		}

		TEST_METHOD(TestMethod2)
		{
			//Service s;

			Assert::AreEqual(10, 10);

		}
	};
}
