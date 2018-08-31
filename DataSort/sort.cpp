// Dylan McKinney
// 8-26-2018
#include "sort.h"

Sort::Sort(QObject* parent): QThread(parent){}

// Create a Sort object using a given algorithm on a given data set, by a given column, in either ascending or descending order
Sort::Sort(QObject* parent, int algorithm, QJsonArray &arr, int column, bool ascending): Sort(parent){
    mAlgorithm = algorithm;
    mArr = arr;
    mColumn = column;
    mAscending = ascending;
}

// Returns the resulting array
// Precondition: Sorting algorithm has completed execution
QJsonArray &Sort::getSortedArray()
{
    return mArr;
}

// Returns the total number of comparisons made during sorting
// Precondition: Sorting algorithm has completed execution
int Sort::getComparisons(){
    return actualComparisons;
}

// Set a sleep time for each comparison to better show relative algorithm efficiency
// Precondition: Sorting has not yet begun
void Sort::setComparisonPenalty(unsigned long value)
{
    comparisonPenalty = value;
}

// Begin thread execution when start() is called
void Sort::run(){
    actualComparisons = 0;
    // Set starting time
    startTime = std::chrono::high_resolution_clock::now();
    stopLock.lock();
    stopped = false;
    stopLock.unlock();
    // Call the appropriate algorithm
    if(mAlgorithm == QUICK_SORT) {
        quickSort(mArr, mColumn, mAscending);
    } else if(mAlgorithm == MERGE_SORT) {
        mergeSort(mArr, mColumn, mAscending);
    } else if(mAlgorithm == SELECTION_SORT) {
        selectionSort(mArr, mColumn, mAscending);
    }
    // Set ending time and calculate duration
    endTime = std::chrono::high_resolution_clock::now();
    duration = endTime - startTime;
}

// Returns the amount of time the algorithm consumed
// Precondition: Sorting algorithm has completed execution
double Sort::getDuration(){
    return duration.count();
}

// Cancel sorting procedure
// Precondition: Sorting has already begun
void Sort::stop(){
    stopLock.lock();
    stopped = true;
    stopLock.unlock();
    emit done(Sort::CANCELLED);
}

// Compare two QJsonValues, with respect to their appropriate types
bool Sort::lessThan(QJsonValue a, QJsonValue b){
    // Apply comparison penalty, if greater than 0
    this->msleep(comparisonPenalty);
    // Increment number of comparisons used by algorithm
    actualComparisons++;
    // Ensure QJsonValues are of the same type
    if (a.type() != b.type()){
        return false;
    }
    // If the value is an array, use array length to determine comparison
    if (a.isArray()) {
        return a.toArray().count() < b.toArray().count();
    } else if (a.isBool()) {
        return a.toBool() < b.toBool();
    } else if (a.isDouble()) {
        return a.toDouble() < b.toDouble();
    } else if (a.isNull() || a.isUndefined()) {
        return false;
    } else if (a.isObject()) {
        // If the value is an object, use raw JSON string to determine comparison
        // Result is lexicographical order, by the first character which is different
        QJsonDocument aDoc(a.toObject());
        QString aString(aDoc.toJson(QJsonDocument::Compact));
        QJsonDocument bDoc(b.toObject());
        QString bString(bDoc.toJson(QJsonDocument::Compact));
        return aString.compare(bString) < 0;
    } else if (a.isString()) {
        return a.toString().compare(b.toString()) < 0;
    }

    return false;
}

// Returns the index of the minimum element in an array, from start to end-1
// Required by selectionSort()
int Sort::findMin(QJsonArray &arr, int column, int start, int end) {
    if (arr[start].isObject()){
        QJsonObject min = arr[start].toObject();
        int index = start;
        for (int i = start + 1; i < end; ++i) {
            stopLock.lock();
            if(stopped){
                stopLock.unlock();
                return -1;
            }
            stopLock.unlock();
            if(arr[i].isObject()){
                QJsonObject objI = arr[i].toObject();
                if (lessThan(objI[objI.keys()[column]], min[min.keys()[column]])) {
                    min = objI;
                    index = i;
                }
            } else {
                return -1;
            }
        }
        return index;
    } else {
        return -1;
    }
}

// Returns the index of the maximum element in an array, from start to end-1
// Required by selectionSort()
int Sort::findMax(QJsonArray &arr, int column, int start, int end) {
    if (arr[start].isObject()){
        QJsonObject max = arr[start].toObject();
        int index = start;
        for (int i = start + 1; i < end; ++i) {
            stopLock.lock();
            if(stopped){
                stopLock.unlock();
                return -1;
            }
            stopLock.unlock();
            if(arr[i].isObject()){
                QJsonObject objI = arr[i].toObject();
                if (!lessThan(objI[objI.keys()[column]], max[max.keys()[column]])) {
                    max = objI;
                    index = i;
                }
            } else {
                return -1;
            }
        }
        return index;
    } else {
        return -1;
    }
}

// Required by selectionSort()
void Sort::swap(QJsonValueRef a, QJsonValueRef b) {
    QJsonValue temp = a;
    a = b;
    b = temp;
}

// Runs selection sort on a given array
// Best:	O(n^2)
// Average:	O(n^2)
// Worst:	O(n^2)
void Sort::selectionSort(QJsonArray &arr, int column, bool ascending) {
    for (int i = 0; i < arr.count(); ++i) {
        emit progress(Sort::SELECTION_SORT, qFloor((i / (0.0 + arr.count())) * 100));
        int index = i;
        if (ascending) {
            index = findMin(arr, column, i, arr.count());
        } else {
            index = findMax(arr, column, i, arr.count());
        }
        if (index == -1) {
            break;
        }
        if (index != i) {
            swap(arr[i], arr[index]);
        }
    }
    emit done(Sort::SELECTION_SORT);
}

// Merge function for Merge Sort
void Sort::merge(QJsonArray &arr, int column, int start, int end, int mid, bool ascending) {
    stopLock.lock();
    if(stopped){
        stopLock.unlock();
        return;
    }
    stopLock.unlock();
    int i = start;
    int j = mid + 1;
    int k = start;
    QJsonArray copy(arr);
    while (i <= mid && j <= end) {
        if (arr[i].isObject() && arr[j].isObject()) {
            QJsonObject objI = arr[i].toObject();
            QJsonObject objJ = arr[j].toObject();
            if ((ascending && lessThan(objI[objI.keys()[column]], objJ[objJ.keys()[column]]))
                    || (!ascending && !lessThan(objI[objI.keys()[column]],  objJ[objJ.keys()[column]]))) {
                copy[k] = arr[i];
                i++;
            } else {
                copy[k] = arr[j];
                j++;
            }
            k++;
        } else {
            break;
        }
        emit progress(Sort::MERGE_SORT, qFloor((actualComparisons / (0.0 + estimatedComparisons)) * 100));
    }
    while (i <= mid) {
        copy[k] = arr[i];
        k++;
        i++;
    }
    while (j <= end) {
        copy[k] = arr[j];
        k++;
        j++;
    }
    for (i = start; i < k; i++) {
        arr[i] = copy[i];
    }
}

// Merge Sort recursive calls
void Sort::mergeSort(QJsonArray &arr, int column, int start, int end, bool ascending) {
    stopLock.lock();
    if(stopped){
        stopLock.unlock();
        return;
    }
    stopLock.unlock();
    if (start < end) {
        int mid = (start + end) / 2;
        mergeSort(arr, column, start, mid, ascending);
        mergeSort(arr, column, mid + 1, end, ascending);

        merge(arr, column, start, end, mid, ascending);
    }
}

// Runs merge sort on a given array
// Best:		O(n*log(n))
// Average:	O(n*log(n))
// Worst:	O(n*log(n))
void Sort::mergeSort(QJsonArray &arr, int column, bool ascending) {
    estimatedComparisons = qFloor(arr.count() * std::log2(arr.count()));
    mergeSort(arr, column, 0, arr.count() - 1, ascending);
    emit done(Sort::MERGE_SORT);
}

// Parition function for Quick Sort algorithm
int Sort::partition(QJsonArray &arr, int column, int start, int end, bool ascending) {
    stopLock.lock();
    if(stopped){
        stopLock.unlock();
        return -1;
    }
    stopLock.unlock();
    if(arr[end].isObject()){
        QJsonObject pivot = arr[end].toObject();
        int i = start - 1;
        for (int j = start; j < end; ++j) {
            if(arr[j].isObject()){
                QJsonObject object = arr[j].toObject();
                if ((ascending && lessThan(object[object.keys()[column]], pivot[pivot.keys()[column]])) || (!ascending && !lessThan(object[object.keys()[column]], pivot[pivot.keys()[column]]))) {// may need less than or equals and greater than or equals
                    ++i;
                    swap(arr[i], arr[j]);
                }
            }else{
                return -1;
            }
            int pro = qFloor((actualComparisons / (0.0 + estimatedComparisons)) * 100);
            if (pro > 100) {
                pro = qFloor((actualComparisons / (0.0 + arr.count() * arr.count())) * 100);
            }
            emit progress(Sort::QUICK_SORT, pro);
        }
        swap(arr[i + 1], arr[end]);
        return i + 1;
    }
    return -1;
}

// Quick Sort recursive calls
void Sort::quickSort(QJsonArray &arr, int column, int start, int end, bool ascending) {
    if (start < end) {
        int index = partition(arr, column, start, end, ascending);
        if(index == -1){
            return;
        }
        quickSort(arr, column, start, index - 1, ascending);
        quickSort(arr, column, index + 1, end, ascending);
    }
}

// Runs quick sort on a given array, ascending order by default
// Best:		O(n*log(n)) - variation where best is n
// Average:	O(n*log(n))
// Worst:	O(n^2)
void Sort::quickSort(QJsonArray &arr, int column, bool ascending) {
    estimatedComparisons = qFloor(arr.count() * std::log2(arr.count()));
    quickSort(arr, column, 0, arr.count() - 1, ascending);
    emit done(Sort::QUICK_SORT);
}
