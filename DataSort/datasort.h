// Dylan McKinney
// 8-26-2018
#ifndef DATASORT_H
#define DATASORT_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTableWidget>
#include <iterator>
#include <sort.h>
#include <tablemanager.h>

namespace Ui {
class DataSort;
}

// Responsible for handling widgets and displaying data to the main application window
class DataSort : public QMainWindow
{
    Q_OBJECT

public:
    explicit DataSort(QWidget *parent = nullptr);
    ~DataSort();

private slots:
    void on_actionOpen_triggered(); // Called when File->Open is pressed in the menu bar
    void headerClicked(int); // Called when a table header is clicked to sort data by that column
    void on_cancelButton_clicked(); // Called when the Cancel Sorting button is pressed during sorting
    void onSortingDone(int); // Called when a Sort procedure completes execution
    void onTableDone(); // Called once the TableManager completes table construction following a sort
    void on_actionExit_triggered(); // Called when File->Exit is pressed in the menu bar
    void onProgress(int, int); // Called whenever a Sort procedure emits a progress signal
    void on_spinBox_valueChanged(int arg1); // Called whenever the comparison penalty spinbox value is changed
    void on_actionSave_as_triggered(); // Called when File->Save as is pressed in the menu bar

private:
    unsigned long comparisonPenalty = 0; // Will contain the value of the comparison penalty spinbox, to be given to a Sort procedure
    Ui::DataSort *ui; // Provides access to GUI elements
    QJsonArray arr; // Contains the array data loaded from a .json file
    int sortColumn = 0; // The column by which data will be sorted. Needed to determine whether to toggle ascending value
    bool ascending = true; // Whether the sorting algorithms are to run in ascending or descending order
    void sort(); // Will create 3 Sort objects using different sorting algorithms and run them on independent threads
    TableManager* tableManager = nullptr; // Provides non-blocking GUI manipulation for reloading table data
    Sort* quickSort = nullptr; // Quick sort procedure to run in a separate thread
    Sort* mergeSort = nullptr; // Merge sort procedure to run in a separate thread
    Sort* selectionSort = nullptr; // Selection sort procedure to run in a separate thread
    bool quickSortDone = false; // True once done signal is received from quickSort
    bool mergeSortDone = false; // True once done signal is received from mergeSort
    bool selectionSortDone = false; // True once done signal is received from selectionSort
    bool cancelled = false; // True if sorting was cancelled
    void setSortStatusVisibility(bool); // Hide or show all labels and progress bars for sorting procedures
    void profilingResults(); // Generate results for sort procedures
    QString compareTime(double timeA, double timeB, double timeC); // Designate a sort procedure as fastest, second, or slowest
};

#endif // DATASORT_H
