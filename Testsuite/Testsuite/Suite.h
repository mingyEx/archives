//: TestSuite:Suite.h
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
#ifndef SUITE_H
#define SUITE_H
#include <vector>
#include <stdexcept>
#include "Test.h"
using std::vector;
using std::logic_error;

namespace TestSuite {

	class TestSuiteError : public logic_error {
	public:
		TestSuiteError(const string& s = "")
			: logic_error(s) {}
	};

	class Suite {
		string name;
		ostream* osptr;
		vector<Test*> tests;  //所以套件是“一系列测试”的意思？
		void reset();
		// Disallowed ops:
		Suite(const Suite&)=delete;
		Suite& operator=(const Suite&)=delete;
	public:
		Suite(const string& name, ostream* osptr = &cout)
			: name(name) {
			this->osptr = osptr;
		}
		string getName() const { return name; }
		long getNumPassed() const;
		long getNumFailed() const;
		const ostream* getStream() const { return osptr; }
		void setStream(ostream* osptr) { this->osptr = osptr; }
		void addTest(Test* t) throw(TestSuiteError);
		void addSuite(const Suite&);
		void run();  // Calls Test::run() repeatedly
		long report() const;
		void free();  // Deletes tests
	};

} // namespace TestSuite
#endif
