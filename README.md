# ATM_USING_ESP32
This project is a part of evaluation for Embedded Systems course instructed by Ankit A. Bhurane and Amit Agarwal.

Consider an ATM machine system to be implemented using ESP32. A user should be able to login the system using a username and password. Let username and password along with an opening balance of 15000 be already available in a Google Spreadsheet.
Post identification,  a user should be able to debit and/or credit a said amount in multiple of 100. 
Post Transaction, the balance should get modified and a summary including the opening balance, debit/ credit Transactions and currect balance should be seen in Google Spreadsheet and Serial Monitor.

Here, telegram bot has been used for taking input and following additional functionalites have been implemented - Any new user is given an option of registration and any registered user can view his/her last 5 transactions.
