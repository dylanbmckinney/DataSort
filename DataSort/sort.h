// Dylan McKinney
// 8-26-2018
#ifndef SORT_H
#define SORT_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>
#include <QtCore>
#include <QThread>
#include <QMutex>
#include <cmath>
#include <chrono>

// Class to run a specified sorting algorithm on a given QJsonArray, by column, in either ascending or descending order
class Sort: public QThread
{
    Q_OBJECT
public:
    static const int QUICK_SORT = 0; // Specify that the algorithm to be used is Quick Sort
    static const int MERGE_SORT = 1; // Specify that the algorithm to be used is Merge Sort
    static const int SELECTION_SORT = 2; // Specify that the algorithm to be used is Selection Sort
    static const int CANCELLED = 3; // Specify in a done signal that sorting has been cancelled
    explicit Sort(QObject* parent = nullptr);
    Sort(QObject *parent, int algorithm, QJsonArray &arr, int column, bool ascending);
    QJsonArray& getSortedArray(); // Returns the resulting array
    void run(); // Begin thread execution when start() is called
    void stop(); // Cancel sorting procedure
    double getDuration(); // Returns the amount of time the algorithm consumed
    int getComparisons(); // Returns the total number of comparisons made during sorting
    void setComparisonPenalty(unsigned long value); // Set a sleep time for each comparison to better show relative algorithm efficiency

signals:
    void done(int); // Emitted once sorting is finished or cancelled
    void progress(int, int); // Emitted after a significant step of algorithm execution, with an estimated progress value
private:
    unsigned long comparisonPenalty = 0; // Sleep time alotted for each comparison made by the algorithm, in milliseconds
    int estimatedComparisons; // Estimated number of comparisons needed by the corresponding sorting algorithm
    int actualComparisons; // Number of times the lessThan function has been called by the algorithm
    QMutex stopLock; // Ensure safe access to the stopped bool during execution
    bool stopped; // Denote whether sorting should continue normally or break execution until done
    int mAlgorithm; // The algorithm used by an instance of this class
    int mColumn; // The column this instance is to sort
    bool mAscending; //  The order to be used by the sorting algorithm
    QJsonArray mArr; // The data to be sorted
    void quickSort(QJsonArray &arr, bool ascending); // Entry point for Quick Sort algorithm
    void quickSort(QJsonArray &arr, int start, int end, bool ascending); // Quick Sort recursive calls
    bool lessThan(QJsonValue a, QJsonValue b); // Compare two QJsonValues, with respect to their appropriate types
    int findMin(QJsonArray &arr, int column, int start, int end); // Find the smallest element in a given range, for Selection Sort
    int findMax(QJsonArray &arr, int column, int start, int end); // Find the largest element in a given range, for Selection Sort
    void selectionSort(QJsonArray &arr, int column, bool ascending = true); // Entry point for Selection Sort algorithm
    void swap(QJsonValueRef a, QJsonValueRef b); // Swap two QJsonValues, by reference
    void merge(QJsonArray &arr, int column, int start, int end, int mid, bool ascending); // Merge function for Merge Sort
    void mergeSort(QJsonArray &arr, int column, int start, int end, bool ascending); // Merge Sort recursive calls
    void mergeSort(QJsonArray &arr, int column, bool ascending = true); // Entry point for Merge Sort
    int partition(QJsonArray &arr, int column, int start, int end, bool ascending); // Parition function for Quick Sort algorithm
    void quickSort(QJsonArray &arr, int column, int start, int end, bool ascending); // Quick Sort recursive calls
    void quickSort(QJsonArray &arr, int column, bool ascending); // Entry point for Quick Sort
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime, endTime; // time points for measuring execution time
    std::chrono::duration<double> duration; // interval of time during execution
};

#endif // SORT_H
