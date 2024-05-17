#include "pch.h"
#include "CppUnitTest.h"
#include "../LB_12.13_close.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestAddEmployee)
		{
			HashTable hashTable(10);
			Employee employee;
			employee.surname = "Doe";
			employee.initials = "J.D.";
			employee.position = "Developer";
			employee.yearOfHire = 2020;
			employee.salary = 50000.0;

			Assert::IsTrue(hashTable.AddEmployee(employee));
		}

		TEST_METHOD(TestRemoveEmployee)
		{
			HashTable hashTable(10);
			Employee employee;
			employee.surname = "Doe";
			employee.initials = "J.D.";
			employee.position = "Developer";
			employee.yearOfHire = 2020;
			employee.salary = 50000.0;

			hashTable.AddEmployee(employee);
			Assert::IsTrue(hashTable.RemoveEmployee("Doe"));
		}
	};
}
