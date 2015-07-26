package com.cavaco.expensetracker.model;

import android.content.ContentValues;
import android.database.Cursor;

public class Transaction extends ModelBase{
	private int type; // ID of type
	private String date;
	private int account; // ID of account
	private float ammount;
	private String note;
	private int currency; // ID of currency used
	
	public static final String TABLE_NAME = "transactions";
	
    private static final String KEY_TYPE = "type";
    private static final String KEY_DATE = "date";
    private static final String KEY_ACCOUNT = "account";
    private static final String KEY_AMMOUNT = "ammount";
    private static final String KEY_NOTE = "note";
    private static final String KEY_CURRENCY = "currency";
    
    protected static final String[] COLUMNS = {KEY_ID,KEY_TYPE,KEY_DATE,KEY_ACCOUNT,KEY_AMMOUNT,KEY_NOTE,KEY_CURRENCY};

    public String getCreateTableString(){
    	return  "CREATE TABLE " + TABLE_NAME + " ( " +
    		KEY_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, " + 
            KEY_TYPE + " INTEGER NOT NULL, " +
            KEY_DATE + " TEXT, " +
            KEY_ACCOUNT + " INTEGER NOT NULL, " +
            KEY_AMMOUNT + " FLOAT NOT NULL, " +
            KEY_NOTE + " TEXT, " +
    		KEY_CURRENCY + " INTEGER NOT NULL, " +
    		"FOREIGN KEY(" + KEY_TYPE + ") REFERENCES " + Type.TABLE_NAME + "(" + Type.KEY_ID + "), " +
    		"FOREIGN KEY(" + KEY_ACCOUNT + ") REFERENCES " + Account.TABLE_NAME + "(" + Account.KEY_ID + "), " +
    		"FOREIGN KEY(" + KEY_CURRENCY + ") REFERENCES " + Currency.TABLE_NAME + "(" + Currency.KEY_ID + ")" +
    		")";
    }
    
    public Transaction(){}
	 
	public Transaction(int type, String date, int account, float ammount, String note, int currency) {
	    super();
	    this.type = type;
	    this.date = date;
	    this.account = account;
	    this.ammount = ammount;
	    this.note = note;
	    this.currency = currency;
	}
	
	public Transaction(Cursor cursor){
		super();
		this.setFromCursor(cursor);
	}
	 
	@Override
    public ModelBase createFromCursor(Cursor cursor){
    	return new Transaction(cursor);
    }
    
	@Override
	public ContentValues getValues(){
		ContentValues values = new ContentValues();
    	values.put(KEY_TYPE, type); 
    	values.put(KEY_DATE, date);
    	values.put(KEY_ACCOUNT, account);
    	values.put(KEY_AMMOUNT, ammount);
    	values.put(KEY_NOTE, note);
    	values.put(KEY_CURRENCY, currency);
    	return values;
	}

	@Override
	public void setFromCursor(Cursor cursor)
	{
        this.id = Integer.parseInt(cursor.getString(0));
        this.type = Integer.parseInt(cursor.getString(1));
        this.date = cursor.getString(2);
        this.account = Integer.parseInt(cursor.getString(3));
        this.ammount = Float.parseFloat(cursor.getString(4));
        this.note = cursor.getString(5);
        this.currency = Integer.parseInt(cursor.getString(2));
	}
	
	@Override
	public String toString() {
	    return "Transaction [id=" + id + ", type=" + type + ", date=" + date + ", ammount" + ammount
	            + "]";
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public int getType() {
		return type;
	}

	public void setType(int type) {
		this.type = type;
	}

	public String getDate() {
		return date;
	}

	public void setDate(String date) {
		this.date = date;
	}

	public int getAccount() {
		return account;
	}

	public void setAccount(int account) {
		this.account = account;
	}

	public float getAmmount() {
		return ammount;
	}

	public void setAmmount(float ammount) {
		this.ammount = ammount;
	}

	public String getNote() {
		return note;
	}

	public void setNote(String note) {
		this.note = note;
	}

	public int getCurrency() {
		return currency;
	}

	public void setCurrency(int currency) {
		this.currency = currency;
	}
	
	public String getTableName(){
		return TABLE_NAME;
	}
}
