#include <chrono>

#include <G4UImanager.hh>
#include <G4UIExecutive.hh>
#include <Randomize.hh>
#ifdef G4VIS_USE
#ifndef	GNEISEMULIB_NO_VIS
#include <G4VisExecutive.hh>
#endif
#endif	//	G4VIS_USE

#include "gneis/runner/BasicRunner.hh"
#include "gneis/util/FileNameBuilder.hh"

gneis::runner::BasicRunner::BasicRunner(int argc, char* argv[]) :
		parser(argc, argv) {

}

gneis::runner::BasicRunner::~BasicRunner() {

}

int gneis::runner::BasicRunner::Run(
		std::function<void(G4RunManager&)> closure) {

	if (parser.GetReturnCode()) {
		return parser.GetReturnCode();
	}

	gneis::util::FileNameBuilder::SetCommonSuffix(parser.GetFileSuffix());

	G4RunManager runManager;

	G4Random::setTheEngine(new CLHEP::RanecuEngine);
	G4Random::setTheSeed(
			parser.GetRandomSeed() >= 0 ?
					parser.GetRandomSeed() : SystemTime());

	auto uiManager = G4UImanager::GetUIpointer();

	if (parser.GetArgc() > 1) {
		closure(runManager);

		// first argument is a script file name
		const G4String command = "/control/execute ";
		const G4String fileName = parser.GetArgv()[1];
		uiManager->ApplyCommand(command + fileName);
	} else {
#ifdef	G4VIS_USE
#ifndef	GNEISEMULIB_NO_VIS
		auto const visManager = new G4VisExecutive("Quiet");
		visManager->Initialize();

		// no arguments passed to executable - run in visual mode
		auto ui = new G4UIExecutive(parser.GetArgc(), parser.GetArgv());
		closure(runManager);
		uiManager->ApplyCommand("/run/initialize");
		uiManager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
		delete ui;
#endif
#endif	//	G4VIS_USE
	}

	return 0;
}

long gneis::runner::BasicRunner::SystemTime() {
	using namespace std::chrono;
	auto const now = time_point_cast < milliseconds > (system_clock::now());
	auto const value = now.time_since_epoch();
	return value.count();
}
