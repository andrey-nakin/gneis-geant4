#include <sstream>
#include <string>

#include <G4UnitsTable.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include "G4UIcmdWithABool.hh"

#include "isnp/facility/Beam5Messenger.hh"

namespace isnp {

namespace facility {

#define DIR "/isnp/beam5/"

static std::unique_ptr<G4UIdirectory> MakeDirectory() {

	auto result = std::make_unique < G4UIdirectory > (DIR);
	result->SetGuidance("ISNP Beam #5 Commands");
	return result;

}

static std::unique_ptr<G4UIcmdWithADoubleAndUnit> MakeDiameter(
		Beam5Messenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithADoubleAndUnit
			> (DIR "diameter", inst);
	result->SetGuidance("Set the final collimator's diameter");
	result->SetParameterName("diameter", false);
	result->SetUnitCategory(G4UnitDefinition::GetCategory("mm"));
	result->AvailableForStates(G4State_PreInit);

	return result;

}

static std::unique_ptr<G4UIcmdWithADoubleAndUnit> MakeAngle(
		Beam5Messenger* const inst) {

	auto result = std::make_unique < G4UIcmdWithADoubleAndUnit
			> (DIR "angle", inst);
	result->SetGuidance("Set the final collimator's diameter");
	result->SetParameterName("angle", false);
	result->SetUnitCategory(G4UnitDefinition::GetCategory("deg"));
	result->AvailableForStates(G4State_PreInit);

	return result;

}

static std::unique_ptr<G4UIcmdWithABool> MakeHaveCollimator(
		Beam5Messenger* const inst, int const collimatorNo) {

	std::ostringstream nameStream;
	nameStream << DIR "haveCollimator" << collimatorNo;
	std::string const name = nameStream.str();

	std::ostringstream guidanceStream;
	guidanceStream << "Set the presense of collimator #" << collimatorNo << ".";
	std::string const guidance = guidanceStream.str();

	auto result = std::make_unique < G4UIcmdWithABool > (name.c_str(), inst);
	result->SetGuidance(guidance.c_str());
	result->SetParameterName("have", false);
	result->AvailableForStates(G4State_PreInit);

	return result;

}

Beam5Messenger::Beam5Messenger(Beam5& facility_) :
		facility(facility_), directory(MakeDirectory()), diameterCmd(
				MakeDiameter(this)), angleCmd(MakeAngle(this)), haveCollimator1Cmd(
				MakeHaveCollimator(this, 1)), haveCollimator2Cmd(
				MakeHaveCollimator(this, 2)), haveCollimator3Cmd(
				MakeHaveCollimator(this, 3)), haveCollimator4Cmd(
				MakeHaveCollimator(this, 4)), haveCollimator5Cmd(
				MakeHaveCollimator(this, 5)) {

}

Beam5Messenger::~Beam5Messenger() {

}

void Beam5Messenger::SetNewValue(G4UIcommand* const command,
		G4String const newValue) {

	if (command == diameterCmd.get()) {
		facility.SetDiameter(diameterCmd->GetNewDoubleValue(newValue));
	} else if (command == angleCmd.get()) {
		facility.SetAngle(angleCmd->GetNewDoubleValue(newValue));
	} else if (command == haveCollimator1Cmd.get()) {
		facility.SetHaveCollimator1(
				haveCollimator1Cmd->GetNewBoolValue(newValue));
	} else if (command == haveCollimator2Cmd.get()) {
		facility.SetHaveCollimator2(
				haveCollimator2Cmd->GetNewBoolValue(newValue));
	} else if (command == haveCollimator3Cmd.get()) {
		facility.SetHaveCollimator3(
				haveCollimator3Cmd->GetNewBoolValue(newValue));
	} else if (command == haveCollimator4Cmd.get()) {
		facility.SetHaveCollimator4(
				haveCollimator4Cmd->GetNewBoolValue(newValue));
	} else if (command == haveCollimator5Cmd.get()) {
		facility.SetHaveCollimator5(
				haveCollimator5Cmd->GetNewBoolValue(newValue));
	}

}

}

}
