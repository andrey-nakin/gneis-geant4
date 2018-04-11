#ifndef isnp_facility_BasicSpallationMessenger_hh
#define isnp_facility_BasicSpallationMessenger_hh

#include <memory>

#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcommand.hh>

#include "isnp/facility/BasicSpallation.hh"

class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAnInteger;

namespace isnp {

namespace facility {

class BasicSpallationMessenger: public G4UImessenger {
public:

	BasicSpallationMessenger(BasicSpallation& aFacility);
	~BasicSpallationMessenger();

	G4String GetCurrentValue(G4UIcommand* command) override;
	void SetNewValue(G4UIcommand*, G4String) override;

private:

	BasicSpallation& facility;
	std::unique_ptr<G4UIdirectory> const directory;
	std::unique_ptr<G4UIcmdWithADoubleAndUnit> const horizontalAngleCmd,
			verticalAngleCmd, distanceCmd, detectorWidthCmd, detectorHeightCmd,
			detectorLengthCmd;
	std::unique_ptr<G4UIcmdWithAnInteger> const verboseCmd;

};

}

}

#endif	//	isnp_facility_BasicSpallationMessenger_hh
