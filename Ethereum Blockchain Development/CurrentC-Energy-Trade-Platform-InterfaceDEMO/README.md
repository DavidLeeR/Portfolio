Copyright © 2018 CurrentC, LLC

# CurrentC Platform (DEMO)
## Webapp platform for natural gas trading on the blockchain (this demo uses Ethereum) <br />
 ***For full functionality, use demo with Ganache Ethereum Simulator***<br />
## Installing and Running the Demo 
### Steps To Use (Windows/Ganache): <br />
1. Download and install Ganache <br />
  http://truffleframework.com/ganache/<br />
2. Install dependencies: <br />
  Node.js: https://nodejs.org/en/ <br />
  Yeoman: open command line and use command: **npm install -g yo** <br />
  Yeoman Webapp: open command line and use command: **npm install -g generator-webapp** <br />
  Bower: open command line and use command: **npm install -g bower** <br />
  Gulp: open command line and use command: **npm install gulp-cli -g** <br />
3. Download this repo as a zip file<br />
4. Extract zip file and open folder <br />
5. Open command line in folder and install web3.js using command: **npm install web3**<br />
  note*: the folder must be listed as the current folder in the command line before using the above command <br />
6. Open command line in folder and set up app using command: **yo webapp**<br />
  6.a. When prompted "Which additional features would you like to include?", uncheck all 3 options (Sass, Bootstrap, Modernzr) and hit enter<br />
  6.b. When promted "Would you like to include jQuery?", type **n** and hit enter<br />
  6.c. When prompted "Choose your style of DSL (Use arrow keys)", highlight **TDD** (the second option) and hit enter<br />
  6.d. When prompted to overwrite **any** file, type **n** and hit enter (this will occur multiple times) <br />
7. Run Ganache <br />
8. Open command line in folder and run app using command: **gulp serve**<br />
9. Your browser will automatically open with the webapp loaded <br />

### Steps To Use (Windows/geth): <br />
Same as above except the following replacements:<br />
1.Install geth node <br />
  https://geth.ethereum.org/downloads/ <br />
  
7.Open command line **outside of folder** and run geth using command: **geth --rpc --rpccorsdomain "*" console --testnet** <br />
  note*: the blockchain must be up to date in order to use this platform, you can check the status of the blockchain by downloading the wallet app and running it while geth is running: https://github.com/ethereum/mist/releases/download/v0.10.0/Ethereum-Wallet-installer-0-10-0.exe <br/>
  
note*: when using geth, you must unlock the account you would like to use manually before launching the CurrentC Platform Demo
  
## Operating the Demo Interface <br />
### "Choose User Address via Index" Section
This input box is used to designate which external user address you would like to use from your node. When using Ganache, these addresses are listed on the "Accounts" page (with the index value on the right hand side). You can set the index of the address you would like use by entering the index number and clicking the "Set Address" button. By default, the interface will use index 0.<br />

### "Set Master Contract" Section
In order to create and send trades using the CurrentC platform, you must deploy or connect your external user address to a Master Contract. This Master Contract can be thought of as your factory for producing and sending trades, and will hold the histories of all your deployed trades. 
<br />

If you would like to start with a new Master Contract, click the "Create New Master Contract" button. If successful, a notification will appear stating the contract has been deployed and the interface will update to show the Master Contract address*.
<br />

If you want to connect to an existing Master Contract, enter the address of the contract into the input box in this section and click the "Connect Existing Master Contract" button. The interface will update to show the connected Master Contract address. Note that when connecting an existing Master Contract there is no error checking, and you must therefore ensure the address is correct beforehand. 
<br />
\* *This notification will appear 2 times, once for deployment of the contract, and once for mining of the contract*<br />

### "Set Peers" Section
In order for the CurrentC platform to receive notifications of trades sent to your external user address, you must connect to other traders' (peers) Master Contracts. This allows for any trade sent to you from that Master Contract to be displayed on the CurrentC platform interface you are using. 
<br />

To connect to another trader's Master Contract, the address of the aforementioned Master Contract must be entered into the first input box in this section labeled "Other Master Contract:". The name or affiliation of the trader that operates the Master Contract may be entered into the second input box labeled "Trader:" for easier readability of multiple peer Master Contracts, but is not necessary. The interface will update displaying all connected peers Master Contract addresses. Note that when connecting to peers there is no error checking, and you must therefore ensure the address is correct beforehand. 
<br />

To display any new trades sent to you (as well as all old trades), click the "Refresh" button in the "Received Trades" section. If a peer trader has sent you a trade before you connected to their Master Contract, clicking the "Refresh" button in the "Received Trades" section after connecting to their Master Contract will display the trade. 

### "Create Trade" Section
This section holds all the parameters available for creating a trade. The "Counterparty Address" field must exactly match the external user address (not the Master Contract address) of the other trader (ie. counterparty) that you wish to send the trade to. All other parameters are optional Any parameters you would like to use must be set at the time of trade creation. Once the trade is deployed, it can no longer be altered. 
<br />

In order to send a purchase trade (ie. purchase natural gas from another trader), fill out the trade form and click the "Purchase" button at the bottom of this section. In order to send a sell trade (ie. sell natural gas to another trader), fill out the trade form and click the "Sell" button at the bottom of this section. 
<br />

After successful trade deployment, a notification will appear and the trade will be listed in the "Deployed Trades" section. If the trade does not appear automatically in the "Deployed Trades" section, click the "Refresh" button. 
<br />

### "Deployed Trades" Section
This section holds all trades deployed from your connected Master Contract. If you change Master Contracts, you may have to click the "Refresh" button in this section for the deployed trades list to be displayed. 
<br />

All trade addresses listed in this section can be clicked on to view the trade.
<br />

### "Received Trades" Section
This section holds all trades sent from a connected peer Master Contract to you (ie. your external user address). In order to update this section to display new trades sent to you (as well as all old trades sent to you), you must click the "Refresh" button. This section will not update automatically. 
<br />

All trade addresses listed in this section can be clicked on to view the trade.
<br />

### Viewing and Accepting or Declining Trades
In order to view a trade, navigate to either the "Deployed Trades" section or the "Received Trades" section and click on a trade address. The interface will update to display the trade below the "Received Trades" section (You may have to scroll down the page). 
<br />

When viewing a trade that was sent to you, the option to accept or decline the trade will be displayed as buttons at the bottom of the trade. 
<br />

If the trade is a sell trade (ie. the counterparty is selling to you), you may enter the amount of ether you wish to send for the trade before accepting, thus, sending the ether to the counterparty.  If the trade is a purchase trade (ie. the counterparty is purchasing from you), accepting the trade will transfer all ether held by the trade to you (ie. the external user address you chose to use).
<br />

Declining any trade will render the trade unusable, and all parameters held by the trade will be deleted. This means you will not be able to read from the trade any longer. Declining a purchase trade will have the previous effect as well as send any ether held by the trade to the trade creator (the purchaser).


