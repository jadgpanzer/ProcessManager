#include "util.h"
#include "error.cpp"
#include "ProcessTools.cpp"
#include "Detect.cpp"
static void showHelp() {
	cout << "This is help for ProcessManager:\n";
	cout << setw(5) << "Option" << setw(35) << "Function "<< setw(45)<<"Parameter\n";
	cout << setw(5) << "-c" << setw(35) << "Create process" << setw(45) << "Process Path\n";
	cout << setw(5) << "-e" << setw(35) << "Show all process" << setw(45)<<"None\n";
	cout << setw(5) << "-kn" << setw(35) << "Kill process by name" << setw(45) <<"Process name\n";
	cout << setw(5) << "-ki" << setw(35) << "Kill process by PID" << setw(45) << "PID\n";
	cout << setw(5) << "-sn" << setw(35) << "Search Process by name" << setw(45) << "Process name\n";
	cout << setw(5) << "-si" << setw(35) << "Search Process by PID" << setw(45) << "PID\n";
	cout << setw(5) << "-h/-help" << setw(35) << "Show all help" << setw(45) << "None\n";
}

static void Status(int now_argc , int argc, const char** argv , int status) {
	if (argv[now_argc] == NULL || now_argc >= argc) {
		return;
	}
	switch (status){
		case 0: {
			if (is_option(argv[now_argc])) {
				regex reg = regex("-e");
				cmatch match;
				if (regex_match(argv[now_argc], match, reg)) {
					enumProcess();
					Status(now_argc + 1, argc, argv, 7);
					break;
				}
				reg = regex("-h|-help");
				if (regex_match(argv[now_argc], match, reg)) {
					showHelp();
					Status(now_argc + 1, argc, argv, 7);
					break;
				}
				reg = regex("-kn");
				if (regex_match(argv[now_argc], match, reg)) {
					Status(now_argc + 1, argc, argv, 1);
					break;
				}
				reg = regex("-sn");
				if (regex_match(argv[now_argc], match, reg)) {
					Status(now_argc + 1, argc, argv, 2);
					break;
				}
				reg = regex("-ki");
				if (regex_match(argv[now_argc], match, reg)) {
					Status(now_argc + 1, argc, argv, 3);
					break;
				}
				reg = regex("-si");
				if (regex_match(argv[now_argc], match, reg)) {
					Status(now_argc + 1, argc, argv, 4);
					break;
				}
				reg = regex("-c");
				if (regex_match(argv[now_argc], match, reg)) {
					Status(now_argc + 1, argc, argv, 5);
					break;
				}
				UnknowOptionError(argv[now_argc]);
			}
			else {
				UnknowOptionError(argv[now_argc]);
			}
			break;
		}
		
		case 1: {
			string name(argv[now_argc]);
			CloseProcess(name);
			Status(now_argc + 1, argc, argv, 6);
			break;
		}
		
		case 2: {
			searchProcess(argv[now_argc]);
			Status(now_argc + 1, argc, argv, 6);
			break;
		}
		
		case 3: {
			if (is_pid(argv[now_argc])) {
				const string str(argv[now_argc]);
				int pid = stoi(str, nullptr, 10);
				CloseProcess(pid);
				Status(now_argc + 1, argc, argv, 6);
			}
			else {

			}
		}

		case 4: {
			if (is_pid(argv[now_argc])) {
				const string str(argv[now_argc]);
				int pid = stoi(str, nullptr, 10);
				searchProcess(pid);
				Status(now_argc + 1, argc, argv, 6);
			}
			else {
				InvalidPIDError(argv[now_argc]);
			}

		}
		
		case 5: {
			if (is_path(argv[now_argc])) {
				const string str(argv[now_argc]);
				int pid = stoi(str, nullptr, 10);
				searchProcess(pid);
				Status(now_argc + 1, argc, argv, 6);
			}
			else {
				InvalidPathError(argv[now_argc]);
			}
		}
		
		case 6: {
			if (argv[now_argc] == NULL || now_argc >= argc) {
				return;
			}
			Status(now_argc, argc, argv, 0);
		}
		case 7: {
			if (argv[now_argc] == NULL || now_argc >= argc) {
				return;
			}
			Status(now_argc, argc, argv, 0);
		}
	}
}

