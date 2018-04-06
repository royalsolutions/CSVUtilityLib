#pragma once

/** \file
 *  The CSVUtilityLib::CSVReader class definitions and its associated output function definitions.
 */

#include <memory>
#include <string>
#include <vector>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

namespace CSVUtilityLib
{

    /**
     *  \class CSVReader CSVReader.h
     *  \brief A utility class used to parse CSV (comma-separated values) files.
     *
     *         Definition of the CSV Format - RFC4180: https://www.rfc-editor.org/rfc/rfc4180.txt
     *         - Each record is located on a separate line, delimited by a line break (CRLF).
     *         - The last record in the file may or may not have an ending line break.
     *         - Within the header and each record, there may be one or more
     *           fields, separated by commas. Each line should contain the same
     *           number of fields throughout the file. Spaces are considered part
     *           of a field and should not be ignored. The last field in the
     *           record must not be followed by a comma.
     *         - Each field may or may not be enclosed in double quotes (however
     *           some programs, such as Microsoft Excel, do not use double quotes
     *           at all). If fields are not enclosed with double quotes, then
     *           double quotes may not appear inside the fields.
     *         - Fields containing line breaks (CRLF), double quotes, and commas
     *           should be enclosed in double-quotes.
     *         - If double-quotes are used to enclose fields, then a double-quote
     *           appearing inside a field must be escaped by preceding it with
     *           another double quote.
     *
     *         \todo Commas and double quotes appearing inside of a field are handled correctly. \n
     *               Line breaks appearing inside of a field are not handled yet. \n
     *               For Canada Census CSV data, this is not an issue. \n
     *               For full compliance with RFC4180, this must be revisited in the future.
     */
    class CSVReader
    {

        public:
            /// A single CSV field.
            typedef std::string CSVField;
            /// A CSV record is made up of at least one CSV field.
            typedef std::vector <CSVField> CSVRow;
            /// A collection of CSV records.
            typedef std::vector <CSVRow> CSVRowVector;

            /// The standard delimiter used in CSV files to separate fields.
            const char CSV_FIELD_DELIMITER = ',';

            /**
             *  \brief The standard character used to enclose fields, when necessary.
             *
             *         Fields containing line breaks, double quotes, and commas should be enclosed.
             *
             *         A double quote inside of a field must be escaped using a double quote.
             */
            const char CSV_FIELD_ENCLOSING_CHAR = '"';

        public:
            /**
             *  \brief Open the specified CSV file for reading.
             *  \param [in] tempCSVFilename The name of the input CSV file.
             */
            CSVReader(std::string tempCSVFilename);

            /**
             *  \brief Check if the CSV file is open.
             *  \return true if the file is open, false otherwise.
             */
            bool IsOpen() const;

            /// Close the current CSV file
            void Close();

            /**
             *  \brief Retrieve the next CSV record.
             *  \param [out] tempCSVRow The retrieved CSV record.
             */
            void GetCSVRow(CSVRow& tempCSVRow);

            /**
            *  \brief Retrieve the remaining records, discarding any empty rows.
            *  \param [out] tempCSVRowVector The retrieved CSV records.
            */
            void GetCSVRows(CSVRowVector& tempCSVRowVector);

            /**
            *  \brief Retrieve up to a specified number of records, discarding any empty rows.
            *
            *         Discarded empty rows are still included in the count.
            *
            *         If EOF is encountered, retrieval will stop early.
            *
            *  \param [out] tempCSVRowVector The retrieved CSV records.
            *  \param [in] tempNumRows The number of rows to retrieve.
            */
            void GetCSVRows(CSVRowVector& tempCSVRowVector, size_t tempNumRows);

            /// Retrieve and discard the next record.
            void SkipCSVRow();

            /**
            *  \brief Retrieve and discard up to a specified number of records.
            *
            *         If EOF is encountered, this process will stop.
            *
            *  \param [in] tempNumRows The number of rows to discard.
            */
            void SkipCSVRows(size_t tempNumRows);

        private:
            std::ifstream inputCSVFile;

    };

}

#include "CSVReader.inl.h"

/**
 *  \brief Simple output of a CSV record for debugging purposes.
 *  \param [in,out] tempOutputStream The output stream.
 *  \param [in] tempCSVRow The CSV record to output.
 */
std::ostream& operator<<(std::ostream& tempOutputStream, const CSVUtilityLib::CSVReader::CSVRow& tempCSVRow);
/**
 *  \brief Simple output of a vector of CSV records for debugging purposes.
 *  \param [in,out] tempOutputStream The output stream.
 *  \param [in] tempCSVRowVector The collection of CSV records to output.
 */
std::ostream& operator<<(std::ostream& tempOutputStream, const CSVUtilityLib::CSVReader::CSVRowVector& tempCSVRowVector);



