pragma solidity ^0.4.4;
//Copyright © 2018 David Ramirez


/*---------------------------------------------------------------------
                           Main Contract 
-----------------------------------------------------------------------*/
contract CurrentC {

  address owner;
  address[] tradeHistory;
  uint historyTracker;

  //constructor: initializes number of trades for history to 0 and makes the address who deployed contract the owner
  function CurrentC() {
    historyTracker = 0;
    owner = msg.sender;
  }

  //turns the contract into read only
  function terminateContract() {
    if (msg.sender == owner) {
      selfdestruct(owner);
    }
  }

  //converts bytes32 type to string, used to read bytes32 type
  function bytes32ToString(bytes32 x) constant returns (string) {
    bytes memory bytesString = new bytes(32);
    uint charCount = 0;
    for (uint j = 0; j < 32; j++) {
        byte char = byte(bytes32(uint(x) * 2 ** (8 * j)));
        if (char != 0) {
            bytesString[charCount] = char;
            charCount++;
        }
    }
    bytes memory bytesStringTrimmed = new bytes(charCount);
    for (j = 0; j < charCount; j++) {
        bytesStringTrimmed[j] = bytesString[j];
    }
    return string(bytesStringTrimmed);
}

  //makes a trade contract between 2 parties and adds to trade history
  function makeTrade(address receiver) payable returns(address tradeContractAddress) {
    address newDeploy =  new TradeContract();//tradeHistory[tradeNum - 1];
    tradeHistory.push(newDeploy);
    historyTracker += 1;
    return newDeploy;
  }

  //returns address of owner of main CCC contract
  function getOwner() returns (address o) {
    o = owner;
  }
  
  //returns current trade num for main contract (ie. the number of trades created (not nec accepted) with main contract)
  function getTradeIndex() returns (uint tn) {
    tn = historyTracker;
  }

  //return address of trade contract at trade history index given 
  function getHistory(uint index) returns (address t) {
    if (index <= (historyTracker - 1)) {
      t = tradeHistory[index];
    }
  }

  /***********************************************************************************************************************
  *  All following "getTrade" functions return the info in readable form from the trade contract, these are needed to     *
  *  convert from bytes32 to string (ie. to read the info)                                                                *
  *************************************************************************************************************************/

  //returns the string "Firm" if trade is firm, "Non-Firm" if not
  function getTradeFirmInfo(uint index) returns (string f) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    bool firm = tradecontract.getFirm();
    
    if (firm == true)
    {
      f = "Firm";
    }

    else if (firm == false)
    {
      f = "Non-Firm";
    }
  }

  //returns month, day, and year (all uint) representing trade contract start date
  function getTradeStartDateInfo(uint index) returns (uint m, uint d, uint y) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    (m,d,y) = tradecontract.getStartDate();
  }

    //returns month, day, and year (all uint) representing trade contract end date
  function getTradeEndDateInfo(uint index) returns (uint m, uint d, uint y) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    (m,d,y) = tradecontract.getEndDate();
  }

  //returns the pipe of the trade at given index
  function getTradePipeInfo(uint index) returns (string p) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    bytes32 pipe = tradecontract.getPipe();
    p = bytes32ToString(pipe);
  }

  //returns the counterparty of the trade at given index
  function getTradeCounterPartyInfo(uint index) returns (string cp) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    bytes32 counterParty = tradecontract.getCounterParty();
    cp = bytes32ToString(counterParty);
  }

  //returns the counterparty address of the trade at given index
  function getTradeCounterPartyAddressInfo(uint index) returns (address cpa) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    address counterPartyAddress = tradecontract.getCounterPartyAdd();
    cpa = counterPartyAddress;
  }

  //returns the party of the trade at given index
  function getTradePartyInfo(uint index) returns (string p) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    bytes32 party = tradecontract.getParty();
    p = bytes32ToString(party);
  }

  //returns the counter party address of the trade at given index
  function getTradePartyAddressInfo(uint index) returns (address pa) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    address partyAddress = tradecontract.getPartyAdd();
    pa = partyAddress;
  }

  //returns the contact of the trade at given index
  function getTradeContactInfo(uint index) returns (string c) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    bytes32 contact = tradecontract.getContact();
    c = bytes32ToString(contact);
  }

  //returns the pricing method of the trade at given index
  function getTradePricingMethodInfo(uint index) returns (string pm) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    bytes32 pricingMethod = tradecontract.getPricingMethod();
    pm = bytes32ToString(pricingMethod);
  }

  //returns the trade index of the trade at given index
  function getTradeIndexInfo(uint index) returns (uint p, uint s) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    (p,s) = tradecontract.getIndex();
  }

  //returns the trade index of the trade at given index
  function getTradeIndexFactorInfo(uint index) returns (uint p, uint s) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    (p,s) = tradecontract.getIndexFactor();
  }

  //returns thefixed price of the trade at given index
  function getTradeFixedPriceInfo(uint index) returns (uint d, uint c) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    (d,c) = tradecontract.getFixedPrice();
  }

  //returns the point of the trade at given index
  function getTradePointInfo(uint index) returns (string p) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    bytes32 point = tradecontract.getPoint();
    p = bytes32ToString(point);
  }

  //returns the volume of the trade at given index
  function getTradeVolumeInfo(uint index) returns (uint d, uint c) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    (d,c) = tradecontract.getVolume();
  }

  //returns the comments of the trade at given index
  function getTradeComments(uint index) returns (string c) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    bytes32 comments = tradecontract.getComments();
    c = bytes32ToString(comments);
  }

  //returns the volume of the trade at given index
  function getTradeTotalVolumeInfo(uint index) returns (uint d, uint c) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    (d,c) = tradecontract.getTotalVolume();
  }

  //returns month, day, and year (all uint) representing trade contract deal date
  function getTradeDealDateInfo(uint index) returns (uint m, uint d, uint y) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    (m,d,y) = tradecontract.getDealDate();
  }

  //returns the total price of the trade at given index
  function getTradeTotalPriceInfo(uint index) returns (uint d, uint c) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    (d,c) = tradecontract.getTotalPrice();
  }
  
  //returns the trader of the trade at given index
  function getTradeTrader(uint index) returns (string t) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    bytes32 trader = tradecontract.getTrader();
    t = bytes32ToString(trader);
  }

  //returns month, day, and year (all uint) representing trade contract entered on date **Note: could make this automatic**
  function getTradeEnteredOnInfo(uint index) returns (uint m, uint d, uint y) {
    address tradeAdd = tradeHistory[index]; 
    TradeContract tradecontract = TradeContract(tradeAdd);

    (m,d,y) = tradecontract.getEnteredOn();
  }
}


/*---------------------------------------------------------------------
                       Contract for Each Trade
-----------------------------------------------------------------------*/
contract TradeContract {

  //for date type
  struct dateStruct {
    uint month;
    uint day;
    uint year;
  }

  //for price type
  struct priceStruct {
    uint dollars;
    uint cents;
  }

  //for float type (floats not yet supported by solidity, cannot do math with this struct, set and read only)
  struct decimalNumberStruct {
    uint prefix;
    uint suffix;
  }

/***********************************************
          MEMBER VARIABLE DECLARATIONS         
************************************************/

  //6
  bool firm;

  //7 
  dateStruct startDate;

  //8 
  dateStruct endDate;

  //9 
  bytes32 pipe;

  //10
  bytes32 counterParty;

  address counterPartyAdd;

  //10.b
  bytes32 party;

  address partyAdd;

  //11
  bytes32 contact;

  //13
  bytes32 pricingMethod;

  //14 
  decimalNumberStruct index;

  //15
  decimalNumberStruct indexFactor;

  //16 
  priceStruct fixedPrice;
  //17 (not sure what this parameter is, need to consult Tim)
  bytes32 point;

  decimalNumberStruct volume;

  //18
  bytes32 comments;

  //19 (solidity does not yet support fixed point numbers)
  decimalNumberStruct totalVolume;

  //20
  dateStruct dealDate;

  //21 
  priceStruct totalPrice;

  //22
  bytes32 trader;

  //23 (seems to be auto filled in front end, will just get from there instead
  //    of aut filling date here)
  dateStruct enteredOn;


  //dummy trade constructor for testing
  /*function TradeContract() {
    setFirm(true);
    setStartDate(1,1,1);
    setEndDate(1,1,1);
    setPipe("pipe");
    setCounterParty("counterparty");
    setCounterPartyAdd(0xb29E2bB965eb031ae45b424cD53b072648B7dE02);
    setParty("party");
    setPartyAdd(0x6A10e778F8Ea5F507631585343D5DC190a9Aa09E);
    setContact("lee3");
    //setPortfolio("portolio");
    setPricingMethod("pricingmethod");
    setIndex(1,1);
    setIndexFactor(1,1);
    setPoint("point");
    setVolume(1,1);
    setFixedPrice(1,1);
    setComments("comment");
    setTotalVolume(1,1);
    setTotalPrice(1,1);
  }*/

  //real use constructor requiring all required parts of trade
  function TradeContract(bool firm, uint startDateM, uint startDateD, uint startDateY, uint endDateM, uint endDateD, uint endDateY, string pipe,
                        string counterParty, address counterPartyAddress, string party, address partyAddress, string contact, string pricingMethod,
                        uint indexP, uint indexS, uint indexFactorP, uint indexFactorS, string point, uint volumeP, uint volumeS, uint fixedPriceD,
                        uint fixedPriceC, string comments, uint totalVolumeP, uint TotalVolumeS) {

                          setFirm(firm);
                          setStartDate(startDateM, startDateD, startDateY);
                          setEndDate(endDateM, endDateD, endDateY);
                          setPipe(pipe);
                          setCounterParty(counterParty);
                          setCounterPartyAdd(counterPartyAddress);
                          setParty(party);
                          setPartyAdd(partyAddress);
                          setContact(contact);
                          setPricingMethod(pricingMethod);
                          setIndex(indexP, indexS);
                          setIndexFactor(indexFactorP, indexFactorS);
                          setPoint(point);
                          setVolume(volumeP, volumeS);
                          setFixedPrice(fixedPriceD, fixedPriceC);
                          setComments(comments);
                          setTotalVolume(totalVolumeP, totalVolumeS);
                        } 




/***********************************************
                 SET FUNCTIONS                   
************************************************/

  function setFirm(bool f) {
    firm = f;
  }

  function setStartDate(uint m, uint d, uint y) {
    startDate.month = m;
    startDate.day = d;
    startDate.year = y;
  }

  function setEndDate(uint m, uint d, uint y) {
    endDate.month = m;
    endDate.day = d;
    endDate.year = y;
  }

  function setPipe(bytes32 p) {
    pipe = p;
  }

  function setCounterParty(bytes32 cp) {
    counterParty = cp;
  }

  function setCounterPartyAdd(address cp) {
    counterPartyAdd = cp;
  }

  function setParty(bytes32 p) {
    party = p;
  }

  function setPartyAdd(address p) {
    partyAdd = p;
  }

  function setContact(bytes32 c) {
    contact = c;
  }

  function setPricingMethod(bytes32 pm) {
    pricingMethod = pm;
  }

  function setIndex(uint p, uint s) {
    index.prefix = p;
    index.suffix = s;
  }

  function setIndexFactor(uint p, uint s) {
    indexFactor.prefix = p;
    indexFactor.suffix = s;
  }

  function setFixedPrice(uint d, uint c) {
    fixedPrice.dollars = d;
    fixedPrice.cents = c;
  }

  function setPoint(bytes32 p) {
    point = p;
  }

  function setVolume(uint p, uint s) {
    volume.prefix = p;
    volume.suffix = s;
  }

  function setComments(bytes32 c) {
    comments = c;
  }

  function setTotalVolume(uint p, uint s) {
    totalVolume.prefix = p;
    totalVolume.suffix = s;
  }

  function setDealDate(uint m, uint d, uint y) {
    dealDate.month = m;
    dealDate.day = d;
    dealDate.year = y;
  }

  function setTotalPrice(uint d, uint c) {
    totalPrice.dollars = d;
    totalPrice.cents = c;
  }

  function setTrader(bytes32 t) {
    trader = t;
  }

  function setEnteredOn(uint m, uint d, uint y) {
    enteredOn.month = m;
    enteredOn.day = d;
    enteredOn.year = y;
  }


/***********************************************
                 GET FUNCTIONS                   
************************************************/

  function getFirm() returns (bool f) {
    f = firm;
  }

  function getStartDate() returns (uint m, uint d, uint y) {
    m = startDate.month;
    d = startDate.day;
    y = startDate.year;
  }

  function getEndDate() returns (uint m, uint d, uint y) {
    m = endDate.month;
    d = endDate.day;
    y = endDate.year;
  }

  function getPipe() returns (bytes32 p) {
    p = pipe;
  }

  function getCounterParty() returns (bytes32 cp) {
    cp = counterParty;
  }

  function getCounterPartyAdd() returns (address cp) {
    cp = counterPartyAdd;
  }

  function getParty() returns (bytes32 p) {
    p = party;
  }

  function getPartyAdd() returns (address p) {
    p = partyAdd;
  }

  function getContact() returns (bytes32 c) {
    c = contact;
  }

  function getPricingMethod() returns (bytes32 pm) {
    pm = pricingMethod;
  }

  function getIndex() returns (uint p, uint s) {
    p = index.prefix;
    s = index.suffix;
  }

  function getIndexFactor() returns (uint p, uint s) {
    p = indexFactor.prefix;
    s = indexFactor.suffix;
  }

  function getFixedPrice() returns (uint d, uint c) {
    d = fixedPrice.dollars;
    c = fixedPrice.cents;
  }

  function getPoint() returns (bytes32 p) {
    p = point;
  }

  function getComments() returns (bytes32 c) {
    c = comments;
  }

  function getVolume() returns (uint p, uint s) {
    p = volume.prefix;
    s = volume.suffix;
  }

  function getTotalVolume() returns (uint p, uint s) {
    p = totalVolume.prefix;
    s = totalVolume.suffix;
  }

  function getDealDate() returns (uint m, uint d, uint y) {
    m = dealDate.month;
    d = dealDate.day;
    y = dealDate.year;
  }

  function getTotalPrice() returns (uint d, uint c) {
    d = totalPrice.dollars;
    c = totalPrice.cents;
  }

  function getTrader() returns (bytes32 t) {
    t = trader;
  }

  function getEnteredOn() returns (uint m, uint d, uint y) {
    m = enteredOn.month;
    d = enteredOn.day;
    y = enteredOn.year;
  }
}
