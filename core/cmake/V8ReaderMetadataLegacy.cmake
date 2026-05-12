set(V8READER_METADATA_LEGACY_SOURCES
	# Support infrastructure required by legacy metadata classes
	../src/Common.cpp
	../src/Parse_tree.cpp
	../src/ModuleTextStorage.cpp

	# P1: metadata model core
	src/metadata/MDO.cpp
	src/metadata/Requisite.cpp
	src/metadata/Comand.cpp
	src/metadata/Moxel.cpp
	src/metadata/Tabular.cpp
	src/metadata/Form.cpp
	src/metadata/BaseMetadataObject.cpp
	src/metadata/MetadataObjectWithSections.cpp
	src/metadata/MetadataObjectInformationRegister.cpp

	# P2: metadata object implementations
	src/metadata/Catalogs.cpp
	src/metadata/Documents.cpp
	src/metadata/Reports.cpp
	src/metadata/DataProcessors.cpp
	src/metadata/Journals.cpp
	src/metadata/Tasks.cpp
	src/metadata/BusinessProceses.cpp
	src/metadata/ExchangePlans.cpp
	src/metadata/ChartOfCalculationTypes.cpp

	src/metadata/InformationRegisters.cpp
	src/metadata/AccumulationRegisters.cpp
	src/metadata/CalculationRegisters.cpp
	src/metadata/AccountingRegisters.cpp
)
