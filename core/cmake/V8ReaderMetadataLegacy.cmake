set(V8READER_METADATA_LEGACY_SOURCES
	# Support infrastructure required by legacy metadata classes
	../src/Common.cpp
	src/metadata/Parse_tree.cpp
	src/metadata/ModuleTextStorage.cpp

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

	# P3: metadata loading/orchestration
	src/metadata/MetaDataManager.cpp

	# Remaining metadata object implementations (BaseMetadataObject descendants)
	src/metadata/Bots.cpp
	src/metadata/ChartOfCharacteristicTypes.cpp
	src/metadata/ChartOfAccounts.cpp
	src/metadata/CommonCommands.cpp
	src/metadata/CommonModules.cpp
	src/metadata/CommonAttributes.cpp
	src/metadata/CommandGroups.cpp
	src/metadata/CommonForms.cpp
	src/metadata/FunctionalOptions.cpp
	src/metadata/FunctionalOptionsParameters.cpp
	src/metadata/DefinedTypes.cpp
	src/metadata/EventSubscriptions.cpp
	src/metadata/CommonPictures.cpp
	src/metadata/FilterCriteria.cpp
	src/metadata/CommonTemplates.cpp
	src/metadata/HTTPServices.cpp
	src/metadata/ExternalDataSources.cpp
	src/metadata/IntegrationServices.cpp
	src/metadata/Interfaces.cpp
	src/metadata/Langs.cpp
	src/metadata/ScheduledJobs.cpp
	src/metadata/Roles.cpp
	src/metadata/Styles.cpp
	src/metadata/StyleItems.cpp
	src/metadata/SettingsStorages.cpp
	src/metadata/SessionParameters.cpp
	src/metadata/TConstants.cpp
	src/metadata/Subsystem.cpp
	src/metadata/WebSocketClients.cpp
	src/metadata/WebServices.cpp
	src/metadata/XDTOPackages.cpp
	src/metadata/WSReferences.cpp

	# Legacy metadata support classes
	src/metadata/Enums.cpp
	src/metadata/Numerators.cpp
	src/metadata/Sequences.cpp
	src/metadata/MetaObject.cpp
	src/metadata/Property.cpp
	src/metadata/CommonMetadataObject.cpp
	src/metadata/MDObject.cpp
)
