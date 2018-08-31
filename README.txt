To run the application on Windows
	Open DataSort.exe located in the Release/ folder

To view the Qt Creator project
	Open DataSort.pro located in the DataSort/ folder
	Project source code is also located here
	(Developed using Qt Creator 4.7.0 Community)

Sample data can be found in the data/ folder
	Source: https://jsonplaceholder.typicode.com/
	Application expects JSON data in the form of an array of JSON objects
	*DataSort expects consistent keys for each object

Application usage
	Load data using File->Open
	Sorting will proceed automatically. Cancel to show original data set.
	To sort the data in a different order, click on one of the table headers.
	Clicking the cancel button will revert the table to its previous state.
	Once sorting is completed, the profiling results will be shown.
	To save your sorted data, use File->Save as.
	A comparison penalty spin box is located at the bottom of the window.
		This allows the user to simulate slower sorting behavior by incurring a wait upon each comparison.
		Leave this set at 0 for normal behavior, or set to another value prior to triggering a sort.
		A value as low as 10 ms can show significant performance penalties for many comparisons on even small data sets.
		This is especially noticeable for O(n^2) algorithms such as Selection Sort, or Quick Sort in its worst case.