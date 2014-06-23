package com.cavaco.expensetracker.model;

import android.content.ContentValues;
import android.database.Cursor;

public class Currency extends ModelBase{
	private int id;
	private String name;
	
	public static final String TABLE_NAME = "currency";
    private static final String KEY_NAME = "name";

    public String getCreateTableString(){
    	return "CREATE TABLE " + TABLE_NAME + " ( " +
        		KEY_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, " + 
                KEY_NAME + " TEXT UNIQUE NOT NULL)";
    }

    public Currency(){}
	
	public Currency(String name)
	{
		this.name = name;
	}
	
	public Currency(Cursor cursor){
		super();
		this.setFromCursor(cursor);
	}
	 
	@Override
    public ModelBase createFromCursor(Cursor cursor){
    	return new Currency(cursor);
    }

	@Override
	public ContentValues getValues(){
		ContentValues values = new ContentValues();
    	values.put(KEY_NAME, name); 
    	return values;
	}

	@Override
	public void setFromCursor(Cursor cursor)
	{
        this.id = Integer.parseInt(cursor.getString(0));
        this.name = cursor.getString(1);
	}
	
    @Override
	public String toString() {
	    return "Currency [id=" + id + ", name=" + name + "]";
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
	
	public String getTableName(){
		return TABLE_NAME;
	}

}
