var sheet_id = "1jC1FVu15N118gusT1Eb0j8ubtRX9gybD4M5T6ncanrk";
var sheet_name = "IandBsheet";
var ss = SpreadsheetApp.openById(sheet_id);
var sheet = ss.getSheetByName(sheet_name);
var i=2;
var j=1;
var k = 1;

function doGet(e){
//  to verify username
  if (e.parameter.data !== undefined){
    var usN = String(e.parameter.data);
    var variable1="A"+String(i)
    var name_on_sheet = String(sheet.getRange(variable1).getValue());
    if(usN==name_on_sheet){
      return ContentService.createTextOutput(String(i));
    }
    while(name_on_sheet!=="0"){
      i+=1;
      variable1="A"+String(i);
      name_on_sheet = String(sheet.getRange(variable1).getValue());
      if(usN==name_on_sheet){
        return ContentService.createTextOutput(String(i));
      }
      if(name_on_sheet=="0"){
        return ContentService.createTextOutput(String(0));
      }
    }
  }

  // to verify password
  if (e.parameter.passrow !== undefined){
    var rowNumber = String(e.parameter.passrow);
    var variable2 = "B"+String(rowNumber);
    var pass_from_sheet = String(sheet.getRange(variable2).getValue());
    return ContentService.createTextOutput(String(pass_from_sheet));
  }
  
  // to read balance amount
  if(e.parameter.user_row!==undefined){
    var inp_row = e.parameter.user_row;
    balamt = sheet.getRange("C"+String(inp_row)).getValue();
    return ContentService.createTextOutput(String(balamt));
  }

  //for credit and debit operations
  if (e.parameter.user_row_val !== undefined && e.parameter.new_bal!==undefined && e.parameter.action!==undefined && e.parameter.amount!==undefined){
    var now = new Date();
    var t1 = "";
    t1+= String(now.getMonth()+1);
    t1+="/";
    t1+= String(now.getDate());
    t1+="/";
    t1+= String(now.getFullYear());

    var t2 = "";
    t2+= String(now.getHours());
    t2+=":";
    t2+= String(now.getMinutes());
    t2+=":";
    t2+= String(now.getSeconds());
    
    var rowidx = String(e.parameter.user_row_val);
    var update_bal = String(e.parameter.new_bal);
    var variable5 = "C"+String(rowidx);
    var old_bal = sheet.getRange(variable5).getValue();
    sheet.getRange(variable5).setValue(update_bal);

    var ss3 = SpreadsheetApp.openById(sheet_id);
    usn3 = String(sheet.getRange("A"+String(rowidx)).getValue()); 
    var act = "";
    if(e.parameter.action == "debit"){
      act = "-" + String(e.parameter.amount);
    }
    else{
      act = "+" + String(e.parameter.amount);
    }
    var sheet2 = ss3.getSheetByName(String(usn3));
    sheet2.appendRow([old_bal,act,update_bal, t1, t2]);
  }
  
  // for registration of new user
  if (e.parameter.nusr !== undefined){
    var newusername = String(e.parameter.nusr);
    var variablex="A"+String(j)
    var newuname_sheet = String(sheet.getRange(variablex).getValue());
    do{
      j+=1;
      variablex="A"+String(j)
      newuname_sheet = String(sheet.getRange(variablex).getValue());
    }while(newuname_sheet!=="0");
    sheet.getRange(variablex).setValue(newusername);
    j+=1;
    variablex="A"+String(j);
    sheet.getRange(variablex).setValue(0);
    return ContentService.createTextOutput(String(j-1));
  }
  
  // to save new password
  if (e.parameter.newpassrow !== undefined && e.parameter.newpass!==undefined){
    var row_newpass = String(e.parameter.newpassrow);
    var newpassstr = String(e.parameter.newpass);
    var range4 = "B"+String(row_newpass);
    sheet.getRange(range4).setValue(newpassstr)
    sheet.getRange("C"+String(row_newpass)).setValue(15000);
    var ss2 = SpreadsheetApp.openById(sheet_id);
    username2 = String(sheet.getRange("A"+String(row_newpass)).getValue());
    ss2.insertSheet(String(username2));
    var sheet2 = ss.getSheetByName(String(username2));
    sheet2.getRange("A1:C1").setValues([["Opening Balance","Transaction","Closing balance", "Date", "Time"]]);
    //sheet2.getRange("A2:C2").setValues([["Start","15000","15000"]]);
  }


  // to get last 5 transactions
  if(e.parameter.roll_no !== undefined){
    var temp = "";
    var range10 = "A" + String(e.parameter.roll_no);
    var name = String(sheet.getRange(range10).getValue());
    var ss4 = SpreadsheetApp.openById(sheet_id);
    var sheet_x = ss4.getSheetByName(String(name));
    var variable11="A"+String(k);
    var op1 = String(sheet_x.getRange(variable11).getValue());
    var lastR = sheet_x.getLastRow();
    while(k <= lastR){
      k+=1;
      variable11="A"+String(k);
      op1 = String(sheet_x.getRange(variable11).getValue());
      if(k<=lastR){
        temp+= op1;temp+= ":";
        var variable8 = "B" + String(k);
        var op2 = String(sheet_x.getRange(variable8).getValue());
        temp +=op2; temp+=":";
        var variable9 = "C" + String(k);
        var op3 = String(sheet_x.getRange(variable9).getValue());
        temp +=op3; temp+=":";
        
      }
      else{
        break;
      }
    }
    return ContentService.createTextOutput(String(temp));
  }
}

