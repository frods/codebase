package com.cavaco.expensetracker.model;

import android.content.ContentValues;
import android.database.Cursor;
import android.widget.EditText;

public class Type extends ModelBase{
	private int id;
	private String name;
	private String type;
	
	public static final String TABLE_NAME = "types";
	
    private static final String KEY_NAME = "name";
    private static final String KEY_TYPE = "type";
    
    public String getCreateTableString(){
    	return  "CREATE TABLE " + TABLE_NAME + " ( " +
    		KEY_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, " + 
            KEY_NAME + " TEXT UNIQUE NOT NULL, " +
    		KEY_TYPE + " TEXT )";
    }
	
    public Type(){}
	
	public Type(String name, String type)
	{
		super();
		this.name = name;
		this.type = type;		
	}

	public Type(Cursor cursor){
		super();
		this.setFromCursor(cursor);
	}
	 
	@Override
    public ModelBase createFromCursor(Cursor cursor){
    	return new Type(cursor);
    }
    
	@Override
	public ContentValues getValues(){
		ContentValues values = new ContentValues();
    	values.put(KEY_NAME, name);
    	values.put(KEY_TYPE, type); 
    	return values;
	}

	@Override
	public void setFromCursor(Cursor cursor)
	{
        this.id = Integer.parseInt(cursor.getString(0));
        this.name = cursor.getString(1);
        this.type = cursor.getString(2);
	}
	
	@Override
	public String toString() {
	    return "Type [id=" + id + ", name=" + name + ", type=" + type + "]";
	}
	
	public void createView(){
		EditText nameEntry = new EditText();
		
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

	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}

	public String getTableName(){
		return TABLE_NAME;
	}
}
