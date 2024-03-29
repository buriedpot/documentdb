
/*-------------------------------------------------------------------------
 * Copyright (c) Microsoft Corporation.  All rights reserved.
 *
 * include/commands/mongo_errors.h
 *
 * Definitions for Mongo errors and the associated error codes.
 *
 *-------------------------------------------------------------------------
 */
#ifndef MONGO_ERRORS_H
#define MONGO_ERRORS_H


#include <postgres.h>
#include <lib/stringinfo.h>
#include <utils/elog.h>

#include "utils/error_utils.h"


/* Represents a Mongo error */
typedef int MongoErrorEreportCode;


/* This gives us the following range: code >= 0 && code <= 2^23 */
#define _ERRCODE_MONGO_ERROR_FIRST MAKE_SQLSTATE('0', '0', '0', '0', 'Y')
#define _ERRCODE_MONGO_ERROR_LAST MAKE_SQLSTATE('0', '0', '0', 'P', 'Y')


/*
 * Given ereport error code belongs to a Mongo error ?
 *
 * Defined as macro so that _DEFINE_MONGO_ERROR can also use it for
 * static assertion.
 */
#define EreportCodeIsMongoError(mongoErrorEreportCode) \
	(mongoErrorEreportCode >= _ERRCODE_MONGO_ERROR_FIRST && \
	 mongoErrorEreportCode <= _ERRCODE_MONGO_ERROR_LAST)


#define _DEFINE_MONGO_ERROR(mongoErrorCodeName, mongoErrorCode) \
	static const MongoErrorEreportCode CppConcat(Mongo, mongoErrorCodeName) = \
		mongoErrorCode + _ERRCODE_MONGO_ERROR_FIRST; \
	StaticAssertDecl( \
		EreportCodeIsMongoError(mongoErrorCode + _ERRCODE_MONGO_ERROR_FIRST), \
		"invalid mongo error code");


/*
 ****************************** SECTION ******************************
 *
 * Define Mongo errors by using native Mongo error codes here.
 *
 * First argument will determine name of the variable that will store
 * the Postgres error code (for ereport()) that corresponds to the
 * Mongo error whose native name is given in the first argument.
 *
 * Second argument is the native Mongo error code.
 *
 * For example;
 *
 * "_DEFINE_MONGO_ERROR(BadValue, 2);" will export "MongoBadValue"
 * so that we can make the following ereport() call to report a
 * "BadValue" error:
 *
 * ereport(ERROR, (errcode(MongoBadValue), errmsg(".....")));
 */
_DEFINE_MONGO_ERROR(InternalError, 1);
_DEFINE_MONGO_ERROR(BadValue, 2);
_DEFINE_MONGO_ERROR(GraphContainsCycle, 5);
_DEFINE_MONGO_ERROR(FailedToParse, 9);
_DEFINE_MONGO_ERROR(TypeMismatch, 14);
_DEFINE_MONGO_ERROR(Overflow, 15);
_DEFINE_MONGO_ERROR(AlreadyInitialized, 23);
_DEFINE_MONGO_ERROR(NamespaceNotFound, 26);
_DEFINE_MONGO_ERROR(IndexNotFound, 27);
_DEFINE_MONGO_ERROR(PathNotViable, 28);
_DEFINE_MONGO_ERROR(CannotBackfillArray, 34);
_DEFINE_MONGO_ERROR(ConflictingUpdateOperators, 40);
_DEFINE_MONGO_ERROR(CursorNotFound, 43);
_DEFINE_MONGO_ERROR(NamespaceExists, 48);
_DEFINE_MONGO_ERROR(DollarPrefixedFieldName, 52);
_DEFINE_MONGO_ERROR(CanNotBeTypeArray, 53);
_DEFINE_MONGO_ERROR(NotSingleValueField, 54);
_DEFINE_MONGO_ERROR(EmptyFieldName, 56);
_DEFINE_MONGO_ERROR(DottedFieldName, 57);
_DEFINE_MONGO_ERROR(ShardKeyNotFound, 61);
_DEFINE_MONGO_ERROR(ImmutableField, 66);
_DEFINE_MONGO_ERROR(CannotCreateIndex, 67);
_DEFINE_MONGO_ERROR(IndexAlreadyExists, 68);
_DEFINE_MONGO_ERROR(InvalidOptions, 72);
_DEFINE_MONGO_ERROR(InvalidNamespace, 73);
_DEFINE_MONGO_ERROR(IndexOptionsConflict, 85);
_DEFINE_MONGO_ERROR(IndexKeySpecsConflict, 86);
_DEFINE_MONGO_ERROR(NotExactValueField, 111);
_DEFINE_MONGO_ERROR(CommandNotSupported, 115);
_DEFINE_MONGO_ERROR(NamespaceNotSharded, 118);
_DEFINE_MONGO_ERROR(ExceededMemoryLimit, 146);
_DEFINE_MONGO_ERROR(DurationOverflow, 159);
_DEFINE_MONGO_ERROR(ViewDepthLimitExceeded, 165);
_DEFINE_MONGO_ERROR(CommandNotSupportedOnView, 166);
_DEFINE_MONGO_ERROR(OptionNotSupportedOnView, 167);
_DEFINE_MONGO_ERROR(AmbiguousIndexKeyPattern, 181);
_DEFINE_MONGO_ERROR(InvalidIndexSpecificationOption, 197);
_DEFINE_MONGO_ERROR(QueryFeatureNotAllowed, 224);
_DEFINE_MONGO_ERROR(MaxSubPipelineDepthExceeded, 232);
_DEFINE_MONGO_ERROR(ConversionFailure, 241);
_DEFINE_MONGO_ERROR(OperationNotSupportedInTransaction, 263);
_DEFINE_MONGO_ERROR(IndexBuildAborted, 276);
_DEFINE_MONGO_ERROR(CollectionUUIDMismatch, 361);
_DEFINE_MONGO_ERROR(DollarRandInvalidArg, 10065);
_DEFINE_MONGO_ERROR(BsonObjectTooLarge, 10334);
_DEFINE_MONGO_ERROR(BackgroundOperationInProgressForNamespace, 12587);
_DEFINE_MONGO_ERROR(Location13026, 13026);
_DEFINE_MONGO_ERROR(Location13027, 13027);
_DEFINE_MONGO_ERROR(Location13068, 13068);
_DEFINE_MONGO_ERROR(DbAlreadyExists, 13297);
_DEFINE_MONGO_ERROR(Location13548, 13548);
_DEFINE_MONGO_ERROR(Location15947, 15947);
_DEFINE_MONGO_ERROR(Location15952, 15952);
_DEFINE_MONGO_ERROR(Location15955, 15955);
_DEFINE_MONGO_ERROR(Location15957, 15957);
_DEFINE_MONGO_ERROR(Location15958, 15958);
_DEFINE_MONGO_ERROR(Location15959, 15959);
_DEFINE_MONGO_ERROR(Location15972, 15972);
_DEFINE_MONGO_ERROR(Location15976, 15976);
_DEFINE_MONGO_ERROR(Location15981, 15981);
_DEFINE_MONGO_ERROR(Location16004, 16004);
_DEFINE_MONGO_ERROR(Location16006, 16006);
_DEFINE_MONGO_ERROR(Location16007, 16007);
_DEFINE_MONGO_ERROR(ExpressionTakesExactlyNArgs, 16020);
_DEFINE_MONGO_ERROR(Location16034, 16034);
_DEFINE_MONGO_ERROR(Location16035, 16035);
_DEFINE_MONGO_ERROR(Location16410, 16410);
_DEFINE_MONGO_ERROR(Location16411, 16411);
_DEFINE_MONGO_ERROR(DollarAddNumericOrDateTypes, 16554);
_DEFINE_MONGO_ERROR(DollarModByZeroProhibited, 16610);
_DEFINE_MONGO_ERROR(DollarModOnlyNumeric, 16611);
_DEFINE_MONGO_ERROR(DollarAddOnlyOneDate, 16612);
_DEFINE_MONGO_ERROR(Location16702, 16702);
_DEFINE_MONGO_ERROR(Location16747, 16747);
_DEFINE_MONGO_ERROR(Location16748, 16748);
_DEFINE_MONGO_ERROR(Location16749, 16749);
_DEFINE_MONGO_ERROR(Location16755, 16755);
_DEFINE_MONGO_ERROR(Location16764, 16764);
_DEFINE_MONGO_ERROR(HashedIndexDoNotSupportArrayValues, 16766);
_DEFINE_MONGO_ERROR(Location16800, 16800);
_DEFINE_MONGO_ERROR(Location16801, 16801);
_DEFINE_MONGO_ERROR(Location16804, 16804);
_DEFINE_MONGO_ERROR(DollarOutTempCollectionCantBeCreated, 16994);
_DEFINE_MONGO_ERROR(Location17040, 17040);
_DEFINE_MONGO_ERROR(Location17041, 17041);
_DEFINE_MONGO_ERROR(Location17042, 17042);
_DEFINE_MONGO_ERROR(Location17043, 17043);
_DEFINE_MONGO_ERROR(Location17044, 17044);
_DEFINE_MONGO_ERROR(Location17045, 17045);
_DEFINE_MONGO_ERROR(Location17046, 17046);
_DEFINE_MONGO_ERROR(Location17047, 17047);
_DEFINE_MONGO_ERROR(Location17048, 17048);
_DEFINE_MONGO_ERROR(Location17049, 17049);
_DEFINE_MONGO_ERROR(DollarCondMissingIfParameter, 17080);
_DEFINE_MONGO_ERROR(DollarCondMissingThenParameter, 17081);
_DEFINE_MONGO_ERROR(DollarCondMissingElseParameter, 17082);
_DEFINE_MONGO_ERROR(DollarCondBadParameter, 17083);
_DEFINE_MONGO_ERROR(DollarSizeRequiresArray, 17124);
_DEFINE_MONGO_ERROR(Location17261, 17261);
_DEFINE_MONGO_ERROR(Location17276, 17276);
_DEFINE_MONGO_ERROR(Location17308, 17308);
_DEFINE_MONGO_ERROR(Location17310, 17310);
_DEFINE_MONGO_ERROR(DocumentAfterUpdateLargerThanMaxSize, 17419);
_DEFINE_MONGO_ERROR(DocumentToUpsertLargerThanMaxSize, 17420);
_DEFINE_MONGO_ERROR(Location18628, 18628);
_DEFINE_MONGO_ERROR(Location18629, 18629);
_DEFINE_MONGO_ERROR(Location18533, 18533);
_DEFINE_MONGO_ERROR(Location18534, 18534);
_DEFINE_MONGO_ERROR(Location18535, 18535);
_DEFINE_MONGO_ERROR(Location18536, 18536);
_DEFINE_MONGO_ERROR(Location18537, 18537);
_DEFINE_MONGO_ERROR(Location28625, 28625);
_DEFINE_MONGO_ERROR(Location28646, 28646);
_DEFINE_MONGO_ERROR(Location28647, 28647);
_DEFINE_MONGO_ERROR(Location28648, 28648);
_DEFINE_MONGO_ERROR(Location28650, 28650);
_DEFINE_MONGO_ERROR(Location28651, 28651);
_DEFINE_MONGO_ERROR(Location28656, 28656);
_DEFINE_MONGO_ERROR(Location28657, 28657);
_DEFINE_MONGO_ERROR(Location28664, 28664);
_DEFINE_MONGO_ERROR(RangeArgumentExpressionArgsOutOfRange, 28667);
_DEFINE_MONGO_ERROR(DollarAbsCantTakeLongMinValue, 28680);
_DEFINE_MONGO_ERROR(ArrayOperatorElemAtFirstArgMustBeArray, 28689);
_DEFINE_MONGO_ERROR(DollarArrayElemAtSecondArgArgMustBeNumeric, 28690);
_DEFINE_MONGO_ERROR(DollarArrayElemAtSecondArgArgMustBe32Bit, 28691);
_DEFINE_MONGO_ERROR(DollarSqrtGreaterOrEqualToZero, 28714);
_DEFINE_MONGO_ERROR(DollarSliceInvalidInput, 28724);
_DEFINE_MONGO_ERROR(DollarSliceInvalidTypeSecondArg, 28725);
_DEFINE_MONGO_ERROR(DollarSliceInvalidValueSecondArg, 28726);
_DEFINE_MONGO_ERROR(DollarSliceInvalidTypeThirdArg, 28727);
_DEFINE_MONGO_ERROR(DollarSliceInvalidValueThirdArg, 28728);
_DEFINE_MONGO_ERROR(DollarSliceInvalidSignThirdArg, 28729);
_DEFINE_MONGO_ERROR(Location28745, 28745);
_DEFINE_MONGO_ERROR(Location28746, 28746);
_DEFINE_MONGO_ERROR(Location28747, 28747);
_DEFINE_MONGO_ERROR(Location28748, 28748);
_DEFINE_MONGO_ERROR(Location28749, 28749);
_DEFINE_MONGO_ERROR(DollarLogArgumentMustBeNumeric, 28756);
_DEFINE_MONGO_ERROR(DollarLogBaseMustBeNumeric, 28757);
_DEFINE_MONGO_ERROR(DollarLogNumberMustBePositive, 28758);
_DEFINE_MONGO_ERROR(DollarLogBaseMustBeGreaterThanOne, 28759);
_DEFINE_MONGO_ERROR(DollarLog10MustBePositiveNumber, 28761);
_DEFINE_MONGO_ERROR(DollarPowBaseMustBeNumeric, 28762);
_DEFINE_MONGO_ERROR(DollarPowExponentMustBeNumeric, 28763);
_DEFINE_MONGO_ERROR(DollarPowExponentInvalidForZeroBase, 28764);
_DEFINE_MONGO_ERROR(Location28765, 28765);
_DEFINE_MONGO_ERROR(DollarLnMustBePositiveNumber, 28766);
_DEFINE_MONGO_ERROR(Location28769, 28769);
_DEFINE_MONGO_ERROR(Location28803, 28803);
_DEFINE_MONGO_ERROR(Location28808, 28808);
_DEFINE_MONGO_ERROR(Location28809, 28809);
_DEFINE_MONGO_ERROR(Location28810, 28810);
_DEFINE_MONGO_ERROR(Location28811, 28811);
_DEFINE_MONGO_ERROR(Location28812, 28812);
_DEFINE_MONGO_ERROR(Location28818, 28818);
_DEFINE_MONGO_ERROR(Location28822, 28822);
_DEFINE_MONGO_ERROR(KeyCannotContainNullByte, 31032);
_DEFINE_MONGO_ERROR(Location31002, 31002);
_DEFINE_MONGO_ERROR(Location31022, 31022);
_DEFINE_MONGO_ERROR(Location31023, 31023);
_DEFINE_MONGO_ERROR(Location31024, 31024);
_DEFINE_MONGO_ERROR(Location31034, 31034);
_DEFINE_MONGO_ERROR(Location31095, 31095);
_DEFINE_MONGO_ERROR(Location31109, 31109);
_DEFINE_MONGO_ERROR(Location31119, 31119);
_DEFINE_MONGO_ERROR(Location31120, 31120);
_DEFINE_MONGO_ERROR(Location31138, 31138);
_DEFINE_MONGO_ERROR(Location31249, 31249);
_DEFINE_MONGO_ERROR(Location31250, 31250);
_DEFINE_MONGO_ERROR(Location31253, 31253);
_DEFINE_MONGO_ERROR(Location31254, 31254);
_DEFINE_MONGO_ERROR(Location31256, 31256);
_DEFINE_MONGO_ERROR(Location31271, 31271);
_DEFINE_MONGO_ERROR(Location31276, 31276);
_DEFINE_MONGO_ERROR(Location31308, 31308);
_DEFINE_MONGO_ERROR(Location31325, 31325);
_DEFINE_MONGO_ERROR(Location31393, 31393);
_DEFINE_MONGO_ERROR(Location31395, 31395);
_DEFINE_MONGO_ERROR(Location34435, 34435);
_DEFINE_MONGO_ERROR(Location31441, 31441);
_DEFINE_MONGO_ERROR(Location34443, 34443);
_DEFINE_MONGO_ERROR(Location34444, 34444);
_DEFINE_MONGO_ERROR(Location34445, 34445);
_DEFINE_MONGO_ERROR(Location34446, 34446);
_DEFINE_MONGO_ERROR(Location34447, 34447);
_DEFINE_MONGO_ERROR(Location34448, 34448);
_DEFINE_MONGO_ERROR(Location34449, 34449);
_DEFINE_MONGO_ERROR(Location34450, 34450);
_DEFINE_MONGO_ERROR(Location34451, 34451);
_DEFINE_MONGO_ERROR(Location34452, 34452);
_DEFINE_MONGO_ERROR(Location34453, 34453);
_DEFINE_MONGO_ERROR(Location34454, 34454);
_DEFINE_MONGO_ERROR(Location34455, 34455);
_DEFINE_MONGO_ERROR(Location34471, 34471);
_DEFINE_MONGO_ERROR(Location34473, 34473);
_DEFINE_MONGO_ERROR(DollarSwitchRequiresObject, 40060);
_DEFINE_MONGO_ERROR(DollarSwitchRequiresArrayForBranches, 40061);
_DEFINE_MONGO_ERROR(DollarSwitchRequiresObjectForEachBranch, 40062);
_DEFINE_MONGO_ERROR(DollarSwitchUnknownArgumentForBranch, 40063);
_DEFINE_MONGO_ERROR(DollarSwitchRequiresCaseExpressionForBranch, 40064);
_DEFINE_MONGO_ERROR(DollarSwitchRequiresThenExpressionForBranch, 40065);
_DEFINE_MONGO_ERROR(DollarSwitchNoMatchingBranchAndNoDefault, 40066);
_DEFINE_MONGO_ERROR(DollarSwitchBadArgument, 40067);
_DEFINE_MONGO_ERROR(DollarSwitchRequiresAtLeastOneBranch, 40068);
_DEFINE_MONGO_ERROR(DollarInRequiresArray, 40081);
_DEFINE_MONGO_ERROR(Location40085, 40085);
_DEFINE_MONGO_ERROR(Location40086, 40086);
_DEFINE_MONGO_ERROR(Location40087, 40087);
_DEFINE_MONGO_ERROR(Location40090, 40090);
_DEFINE_MONGO_ERROR(Location40091, 40091);
_DEFINE_MONGO_ERROR(Location40092, 40092);
_DEFINE_MONGO_ERROR(Location40093, 40093);
_DEFINE_MONGO_ERROR(Location40094, 40094);
_DEFINE_MONGO_ERROR(Location40096, 40096);
_DEFINE_MONGO_ERROR(Location40097, 40097);
_DEFINE_MONGO_ERROR(Location40100, 40100);
_DEFINE_MONGO_ERROR(Location40101, 40101);
_DEFINE_MONGO_ERROR(Location40102, 40102);
_DEFINE_MONGO_ERROR(Location40103, 40103);
_DEFINE_MONGO_ERROR(Location40104, 40104);
_DEFINE_MONGO_ERROR(Location40105, 40105);
_DEFINE_MONGO_ERROR(Location40147, 40147);
_DEFINE_MONGO_ERROR(Location40156, 40156);
_DEFINE_MONGO_ERROR(Location40158, 40158);
_DEFINE_MONGO_ERROR(Location40160, 40160);
_DEFINE_MONGO_ERROR(Location40169, 40169);
_DEFINE_MONGO_ERROR(Location40177, 40177);
_DEFINE_MONGO_ERROR(Location40185, 40185);
_DEFINE_MONGO_ERROR(Location40218, 40218);
_DEFINE_MONGO_ERROR(Location40228, 40228);
_DEFINE_MONGO_ERROR(Location40234, 40234);
_DEFINE_MONGO_ERROR(Location40238, 40238);
_DEFINE_MONGO_ERROR(Location40272, 40272);
_DEFINE_MONGO_ERROR(Location40319, 40319);
_DEFINE_MONGO_ERROR(Location40321, 40321);
_DEFINE_MONGO_ERROR(Location40323, 40323);
_DEFINE_MONGO_ERROR(UnrecognizedCommand, 40324);
_DEFINE_MONGO_ERROR(Location40352, 40352);
_DEFINE_MONGO_ERROR(DollarArrayToObjectRequiresArray, 40386);
_DEFINE_MONGO_ERROR(DollarObjectToArrayRequiresObject, 40390);
_DEFINE_MONGO_ERROR(DollarArrayToObjectAllMustBeObjects, 40391);
_DEFINE_MONGO_ERROR(DollarArrayToObjectIncorrectNumberOfKeys, 40392);
_DEFINE_MONGO_ERROR(DollarArrayToObjectRequiresObjectWithKAndV, 40393);
_DEFINE_MONGO_ERROR(DollarArrayToObjectObjectKeyMustBeString, 40394);
_DEFINE_MONGO_ERROR(DollarArrayToObjectArrayKeyMustBeString, 40395);
_DEFINE_MONGO_ERROR(DollarArrayToObjectAllMustBeArrays, 40396);
_DEFINE_MONGO_ERROR(DollarArrayToObjectIncorrectArrayLength, 40397);
_DEFINE_MONGO_ERROR(DollarArrayToObjectBadInputTypeFormat, 40398);
_DEFINE_MONGO_ERROR(DollarMergeObjectsInvalidType, 40400);
_DEFINE_MONGO_ERROR(UnknownBsonField, 40415);
_DEFINE_MONGO_ERROR(Location40485, 40485);
_DEFINE_MONGO_ERROR(Location40489, 40489);
_DEFINE_MONGO_ERROR(Location40515, 40515);
_DEFINE_MONGO_ERROR(Location40516, 40516);
_DEFINE_MONGO_ERROR(Location40517, 40517);
_DEFINE_MONGO_ERROR(Location40518, 40518);
_DEFINE_MONGO_ERROR(Location40519, 40519);
_DEFINE_MONGO_ERROR(Location40520, 40520);
_DEFINE_MONGO_ERROR(Location40521, 40521);
_DEFINE_MONGO_ERROR(Location40522, 40522);
_DEFINE_MONGO_ERROR(Location40523, 40523);
_DEFINE_MONGO_ERROR(Location40524, 40524);
_DEFINE_MONGO_ERROR(Location40525, 40525);
_DEFINE_MONGO_ERROR(Location40533, 40533);
_DEFINE_MONGO_ERROR(Location40535, 40535);
_DEFINE_MONGO_ERROR(Location40536, 40536);
_DEFINE_MONGO_ERROR(Location40539, 40539);
_DEFINE_MONGO_ERROR(Location40600, 40600);
_DEFINE_MONGO_ERROR(Location40602, 40602);
_DEFINE_MONGO_ERROR(Location50694, 50694);
_DEFINE_MONGO_ERROR(Location50695, 50695);
_DEFINE_MONGO_ERROR(Location50696, 50696);
_DEFINE_MONGO_ERROR(Location50699, 50699);
_DEFINE_MONGO_ERROR(Location50700, 50700);
_DEFINE_MONGO_ERROR(Location50723, 50723);
_DEFINE_MONGO_ERROR(Location50752, 50752);
_DEFINE_MONGO_ERROR(Location50759, 50759);
_DEFINE_MONGO_ERROR(Location51024, 51024);
_DEFINE_MONGO_ERROR(Location51047, 51047);
_DEFINE_MONGO_ERROR(Location51074, 51074);
_DEFINE_MONGO_ERROR(Location51075, 51075);
_DEFINE_MONGO_ERROR(DollarRoundOverflowInt64, 51080);
_DEFINE_MONGO_ERROR(DollarRoundFirstArgMustBeNumeric, 51081);
_DEFINE_MONGO_ERROR(DollarRoundPrecisionMustBeIntegral, 51082);
_DEFINE_MONGO_ERROR(DollarRoundPrecisionOutOfRange, 51083);
_DEFINE_MONGO_ERROR(Location51091, 51091);
_DEFINE_MONGO_ERROR(Location51103, 51103);
_DEFINE_MONGO_ERROR(Location51104, 51104);
_DEFINE_MONGO_ERROR(Location51105, 51105);
_DEFINE_MONGO_ERROR(Location51106, 51106);
_DEFINE_MONGO_ERROR(Location51107, 51107);
_DEFINE_MONGO_ERROR(Location51108, 51108);
_DEFINE_MONGO_ERROR(Location51109, 51109);
_DEFINE_MONGO_ERROR(Location51110, 51110);
_DEFINE_MONGO_ERROR(Location51111, 51111);
_DEFINE_MONGO_ERROR(Location51151, 51151);
_DEFINE_MONGO_ERROR(Location51156, 51156);
_DEFINE_MONGO_ERROR(Location51246, 51246);
_DEFINE_MONGO_ERROR(Location51276, 51276);
_DEFINE_MONGO_ERROR(Location51247, 51247);
_DEFINE_MONGO_ERROR(Location51743, 51743);
_DEFINE_MONGO_ERROR(Location51744, 51744);
_DEFINE_MONGO_ERROR(Location51745, 51745);
_DEFINE_MONGO_ERROR(Location51746, 51746);
_DEFINE_MONGO_ERROR(Location51747, 51747);
_DEFINE_MONGO_ERROR(Location51748, 51748);
_DEFINE_MONGO_ERROR(Location51749, 51749);
_DEFINE_MONGO_ERROR(Location51750, 51750);
_DEFINE_MONGO_ERROR(Location51751, 51751);
_DEFINE_MONGO_ERROR(Location327391, 327391);
_DEFINE_MONGO_ERROR(Location327392, 327392);
_DEFINE_MONGO_ERROR(DollarIfNullRequiresAtLeastTwoArgs, 1257300);
_DEFINE_MONGO_ERROR(DollarRandNonEmptyArgument, 3040501);
_DEFINE_MONGO_ERROR(IntermediateResultTooLarge, 4031700);
_DEFINE_MONGO_ERROR(DollarSetFieldRequiresObject, 4161100);
_DEFINE_MONGO_ERROR(DollarSetFieldUnknownArgument, 4161101);
_DEFINE_MONGO_ERROR(Location4161102, 4161102);
_DEFINE_MONGO_ERROR(Location4161103, 4161103);
_DEFINE_MONGO_ERROR(Location4161104, 4161104);
_DEFINE_MONGO_ERROR(Location4161105, 4161105);
_DEFINE_MONGO_ERROR(Location4161106, 4161106);
_DEFINE_MONGO_ERROR(Location4161107, 4161107);
_DEFINE_MONGO_ERROR(Location4161108, 4161108);
_DEFINE_MONGO_ERROR(Location4161109, 4161109);
_DEFINE_MONGO_ERROR(Location4940400, 4940400);
_DEFINE_MONGO_ERROR(Location4940401, 4940401);
_DEFINE_MONGO_ERROR(Location5107200, 5107200);
_DEFINE_MONGO_ERROR(Location5107201, 5107201);
_DEFINE_MONGO_ERROR(Location5439007, 5439007);
_DEFINE_MONGO_ERROR(Location5439008, 5439008);
_DEFINE_MONGO_ERROR(Location5439009, 5439009);
_DEFINE_MONGO_ERROR(Location5439010, 5439010);
_DEFINE_MONGO_ERROR(Location5439012, 5439012);
_DEFINE_MONGO_ERROR(Location5439013, 5439013);
_DEFINE_MONGO_ERROR(Location5439014, 5439014);
_DEFINE_MONGO_ERROR(Location5439015, 5439015);
_DEFINE_MONGO_ERROR(Location5439016, 5439016);
_DEFINE_MONGO_ERROR(Location5439017, 5439017);
_DEFINE_MONGO_ERROR(Location5439018, 5439018);
_DEFINE_MONGO_ERROR(Location5787801, 5787801);
_DEFINE_MONGO_ERROR(Location5787901, 5787901);
_DEFINE_MONGO_ERROR(Location5787902, 5787902);
_DEFINE_MONGO_ERROR(Location5787903, 5787903);
_DEFINE_MONGO_ERROR(Location5787906, 5787906);
_DEFINE_MONGO_ERROR(Location5787907, 5787907);
_DEFINE_MONGO_ERROR(Location5787908, 5787908);
_DEFINE_MONGO_ERROR(Location5788200, 5788200);
_DEFINE_MONGO_ERROR(Location5858203, 5858203);

/* do not expose helper macro unnecessarily  */
#undef _DEFINE_MONGO_ERROR


/*
 * Prepend error messages of Mongo errors within a PG_CATCH() block.
 * Example usage:
 *
 *   MemoryContext savedMemoryContext = CurrentMemoryContext;
 *   PG_TRY();
 *   {
 *     // perform the stuff that could result in throwing a Mongo error
 *   }
 *   PG_CATCH();
 *   {
 *     // Make sure to switch back to original memory context before
 *     // re-throwing the error.
 *     MemoryContextSwitchTo(savedMemoryContext);
 *
 *     RethrowPrependMongoError(errorPrefix);
 *   }
 *   PG_END_TRY();
 */
static inline void
RethrowPrependMongoError(char *errorPrefix)
{
	ErrorData *errorData = CopyErrorDataAndFlush();

	if (EreportCodeIsMongoError(errorData->sqlerrcode))
	{
		StringInfo newErrorMessageStr = makeStringInfo();
		appendStringInfo(newErrorMessageStr, "%s%s", errorPrefix,
						 errorData->message);
		errorData->message = newErrorMessageStr->data;
	}

	ThrowErrorData(errorData);
}


#endif
