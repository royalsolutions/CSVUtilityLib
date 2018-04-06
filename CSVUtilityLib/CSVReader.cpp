#include "CSVReader.h"

CSVUtilityLib::CSVReader::CSVReader(std::string tempCSVFilename)
{

    inputCSVFile.open(tempCSVFilename);

}

void CSVUtilityLib::CSVReader::GetCSVRow(CSVUtilityLib::CSVReader::CSVRow& tempCSVRow)
{

    tempCSVRow.clear();

    if (!IsOpen())
    {

        return;

    }

    std::string tempCSVRecord;

    // Read an entire CSV record.
    std::getline(inputCSVFile, tempCSVRecord);

    // All data is read up until the EOF is encountered.  No records or fields are dropped if the CSV file is valid.
    if (!inputCSVFile.good())
    {

        Close();

    }

    // Prepare the CSV record to be parsed further.
    std::istringstream tempISStream(tempCSVRecord);

    // Parse the input stringstream until the end of the CSV record.
    while (tempISStream.good())
    {

        bool tempIsCSVFieldComplete = false;
        CSVField tempCSVField;
        ptrdiff_t tempNumQuotationMarks = 0;

        // Extract a single field
        do
        {

            std::string tempString;

            // Read until a comma is encountered.  Extracted text does not include the comma.
            std::getline(tempISStream, tempString, CSV_FIELD_DELIMITER);

            // Double quotes must ALWAYS appear in pairs.
            tempNumQuotationMarks += std::count(tempString.begin(), tempString.end(), CSV_FIELD_ENCLOSING_CHAR);

            // Extracted text is appended to the output CSV field.
            tempCSVField.append(tempString);

            // If the number of double quotes is odd, the current set of extracted text is not a complete CSV field.
            if ((tempNumQuotationMarks % 2) != 0)
            {

                // This is not a valid CSV field so append the comma that was not included above.
                tempCSVField.push_back(CSV_FIELD_DELIMITER);

            }
            else
            {

                // This is a complete field.  Remove the enclosing double quotes if they exist.
                if (tempNumQuotationMarks != 0 && tempCSVField.length() > 1)
                {

                    tempCSVField = tempCSVField.substr(1, tempCSVField.length() - 2);

                }

                tempIsCSVFieldComplete = true;

            }

        }
        while (!tempIsCSVFieldComplete);

        size_t tempPreviousIndex = 0;
        size_t tempCurrentIndex = 0;

        // Escape all single quotes using a single quote.
        while ((tempCurrentIndex = tempCSVField.find("'", tempPreviousIndex)) != std::string::npos)
        {

            tempCSVField.insert(tempCurrentIndex, "'");
            tempPreviousIndex = tempCurrentIndex + 2;

        }

        tempCSVRow.push_back(tempCSVField);

    }

}

void CSVUtilityLib::CSVReader::GetCSVRows(CSVUtilityLib::CSVReader::CSVRowVector& tempCSVRowVector)
{

    tempCSVRowVector.clear();

    CSVRow tempCSVRow;

    while (IsOpen())
    {

        GetCSVRow(tempCSVRow);

        if (!tempCSVRow.empty())
        {

            tempCSVRowVector.push_back(tempCSVRow);

        }

    }

}

void CSVUtilityLib::CSVReader::GetCSVRows(CSVUtilityLib::CSVReader::CSVRowVector& tempCSVRowVector, size_t tempNumRows)
{

    tempCSVRowVector.clear();

    CSVRow tempCSVRow;

    for (size_t i = 0; IsOpen() && i < tempNumRows; i++)
    {

        GetCSVRow(tempCSVRow);

        if (!tempCSVRow.empty())
        {

            tempCSVRowVector.push_back(tempCSVRow);

        }

    }

}

void CSVUtilityLib::CSVReader::SkipCSVRow()
{

    if (!IsOpen())
    {

        return;

    }

    std::string tempCSVRecord;

    // Read an entire CSV record and subsequently discard it.
    std::getline(inputCSVFile, tempCSVRecord);

    // All records are read up until the EOF.  No records are dropped.
    if (!inputCSVFile.good())
    {

        Close();

    }

}

void CSVUtilityLib::CSVReader::SkipCSVRows(size_t tempNumRows)
{

    for (size_t i = 0; IsOpen() && i < tempNumRows; i++)
    {

        SkipCSVRow();

    }

}

std::ostream& operator<<(std::ostream& tempOutputStream, const CSVUtilityLib::CSVReader::CSVRow& tempCSVRow)
{

    tempOutputStream << "****************************************" << std::endl;
    tempOutputStream << std::endl;
    tempOutputStream << "Num fields: " << tempCSVRow.size() << std::endl;
    tempOutputStream << std::endl;

    for (CSVUtilityLib::CSVReader::CSVField tempCSVField : tempCSVRow)
    {

        tempOutputStream << tempCSVField << std::endl;

    }

    tempOutputStream << std::endl;
    tempOutputStream << "****************************************" << std::endl;

    return tempOutputStream;

}

std::ostream& operator<<(std::ostream& tempOutputStream, const CSVUtilityLib::CSVReader::CSVRowVector& tempCSVRowVector)
{

    tempOutputStream << "********************************************************************************" << std::endl;
    tempOutputStream << std::endl;
    tempOutputStream << "Num rows: " << tempCSVRowVector.size() << std::endl;
    tempOutputStream << std::endl;

    for (CSVUtilityLib::CSVReader::CSVRow tempCSVRow : tempCSVRowVector)
    {

        tempOutputStream << tempCSVRow << std::endl;

    }

    tempOutputStream << "********************************************************************************" << std::endl;

    return tempOutputStream;

}



