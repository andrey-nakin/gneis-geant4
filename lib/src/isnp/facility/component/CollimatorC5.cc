#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4LogicalVolume.hh>
#include <G4VisAttributes.hh>
#include <G4SubtractionSolid.hh>
#include <G4Tubs.hh>

#include "isnp/facility/component/CollimatorC5.hh"
#include "isnp/repository/Colours.hh"
#include "isnp/util/NameBuilder.hh"

const G4double isnp::facility::component::CollimatorC5::length = 1000 * mm;

G4LogicalVolume* isnp::facility::component::CollimatorC5::AsCylinder(
		G4double const outerRadius, G4double const diameter) {

	return AsCylinder(GetDefaultName(), outerRadius, diameter);
}

G4LogicalVolume* isnp::facility::component::CollimatorC5::AsCylinder(
		const G4String &name, G4double const outerRadius,
		G4double const diameter) {

	return MakeLogical(MakeCylinder(name, GetLength(), outerRadius, diameter));
}

G4LogicalVolume* isnp::facility::component::CollimatorC5::Instance(
		G4VSolid* const outer, G4double const diameter) {

	return Instance(GetDefaultName(), outer, diameter);
}

G4LogicalVolume* isnp::facility::component::CollimatorC5::Instance(
		const G4String &name, G4VSolid* const outer, G4double const diameter) {

	const auto aperture = new G4Tubs(name, 0.0, HalfOf(diameter),
			HalfOf(GetLength()), 0.0 * deg, 360.0 * deg);
	const auto solid = new G4SubtractionSolid(name, outer, aperture);
	return MakeLogical(solid);
}

G4String isnp::facility::component::CollimatorC5::GetDefaultName() {
	return util::NameBuilder::Make("Collimator", "C5");
}

G4double isnp::facility::component::CollimatorC5::GetLength() {
	return length;
}

G4double isnp::facility::component::CollimatorC5::GetHalfLength() {
	return HalfOf(GetLength());
}

G4LogicalVolume* isnp::facility::component::CollimatorC5::MakeLogical(
		G4VSolid * const solid) {

	const auto nist = G4NistManager::Instance();

	const auto logic = new G4LogicalVolume(solid,
			nist->FindOrBuildMaterial("BR05C5S5"), solid->GetName());
	logic->SetVisAttributes(G4VisAttributes(repository::Colours::Bronze()));

	return logic;
}