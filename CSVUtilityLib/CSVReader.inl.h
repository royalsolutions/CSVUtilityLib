#pragma once

/** \file
*  The inline implementations of some CSVUtilityLib::CSVReader member functions.
*/

inline bool CSVUtilityLib::CSVReader::IsOpen() const { return inputCSVFile.is_open(); }

inline void CSVUtilityLib::CSVReader::Close() { inputCSVFile.close(); }



