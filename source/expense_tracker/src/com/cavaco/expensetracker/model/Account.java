package com.cavaco.expensetracker.model;

import android.content.ContentValues;
import android.database.Cursor;

public class Account extends ModelBase{
	private int id;
	private String name;
	private int currency;
	
	public static final String TABLE_NAME = "account";
	
    private static final String KEY_NAME = "name";
    private static final String KEY_CURRENCY = "currency";

    public String getCreateTableString(){
    	return  "CREATE TABLE " + TABLE_NAME + " ( " +
    		KEY_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, " + 
            KEY_NAME + " TEXT UNIQUE NOT NULL, " +
    		KEY_CURRENCY + " INTEGER, " +
    		"FOREIGN KEY(" + KEY_CURRENCY + ") REFERENCES " + Currency.TABLE_NAME + "(" + Currency.KEY_ID + "))";
    }
	
    public Account(){}
	
	public Account(String name, int currency)
	{
		super();
		this.name = name;
		this.currency = currency;
	}
	
	public Account(Cursor cursor){
		super();
		this.setFromCursor(cursor);
	}
	 
	@Override
    public ModelBase createFromCursor(Cursor cursor){
    	return new Account(cursor);
    }

	@Override
	public ContentValues getValues(){
		ContentValues values = new ContentValues();
    	values.put(KEY_NAME, name); 
    	values.put(KEY_CURRENCY, currency);
    	return values;
	}
	
	@Override
	public void setFromCursor(Cursor cursor)
	{
        this.id = Integer.parseInt(cursor.getString(0));
        this.name = cursor.getString(1);
        this.currency = Integer.parseInt(cursor.getString(2));
	}
	
    @Override
	public String toString() {
	    return "Account [id=" + id + ", name=" + name + ", currency=" + currency + "]";
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
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
