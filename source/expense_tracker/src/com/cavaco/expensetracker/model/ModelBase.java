package com.cavaco.expensetracker.model;

import java.util.LinkedList;
import java.util.List;

import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.util.Log;

import com.cavaco.expensetracker.SQLiteHelper;

public class ModelBase {
	protected int id;
	
	public static final String TABLE_NAME = "modelBase";
	
    protected static final String KEY_ID = "id";

    protected static final String[] COLUMNS = {};

    public ModelBase(){}
	 
	public ModelBase(Cursor cursor){
		super();
		this.setFromCursor(cursor);
	};
	
    public ModelBase createFromCursor(Cursor cursor){
    	return new ModelBase(cursor);
    }
    
	public void setFromCursor(Cursor cursor)
	{
        this.id = Integer.parseInt(cursor.getString(0));
	}
    public String getDropTableString(){
    	return "DROP TABLE IF EXISTS " + this.getTableName();
    }

    public ContentValues getValues(){
		ContentValues values = new ContentValues();
		
		return values;
	};
	
    public void addToDb(SQLiteHelper dbHelper){
        //for logging
    	Log.d("addToDb", this.toString()); 

    	// 1. get reference to writable DB
    	SQLiteDatabase db = dbHelper.getWritableDatabase();

    	// 2. create ContentValues to add key "column"/value
    	ContentValues values = this.getValues();

    	// 3. insert
    	db.insert(this.getTableName(), // table
    			null, //nullColumnHack
    			values); // key/value -> keys = column names/ values = column values

    	// 4. close
    	db.close(); 
    }
    
    public void loadFromDb(SQLiteHelper dbHelper, int id){
   	 
        // 1. get reference to readable DB
        SQLiteDatabase db = dbHelper.getReadableDatabase();
     
        // 2. build query
        Cursor cursor = 
                db.query(this.getTableName(), // a. table
                COLUMNS, // b. column names
                KEY_ID + " = ?", // c. selections 
                new String[] { String.valueOf(id) }, // d. selections args
                null, // e. group by
                null, // f. having
                null, // g. order by
                null); // h. limit
     
        // 3. if we got results get the first one
        if (cursor != null)
            cursor.moveToFirst();
     
        // 4. build book object
        this.setFromCursor(cursor);
     
        //log 
        Log.d("getModel("+id+")", this.toString());
     
    }

    public List<ModelBase> getAllFromDb(SQLiteHelper dbHelper) {
        List<ModelBase> models = new LinkedList<ModelBase>();
  
        // 1. build the query
        String query = "SELECT  * FROM " + this.getTableName();
  
        // 2. get reference to writable DB
        SQLiteDatabase db = dbHelper.getReadableDatabase();
        Cursor cursor = db.rawQuery(query, null);
  
        // 3. go over each row, build book and add it to list
        ModelBase model = null;
        if (cursor.moveToFirst()) {
            do {
                model = this.createFromCursor(cursor);
  
                // Add transaction to transactions
                models.add(model);
            } while (cursor.moveToNext());
        }
  
        Log.d("getAllTransactions()", models.toString());
  
        // return models
        return models;
    }

    public int updateDb(SQLiteHelper dbHelper) {
   	 
        // 1. get reference to writable DB
        SQLiteDatabase db = dbHelper.getWritableDatabase();
     
        // 2. create ContentValues to add key "column"/value
        ContentValues values = this.getValues();
     
        // 3. updating row
        int i = db.update(this.getTableName(), //table
                values, // column/value
                KEY_ID+" = ?", // selections
                new String[] { String.valueOf(id) }); //selection args
     
        // 4. close
        db.close();
     
        return i;
    }

    public void deleteFromDb(SQLiteHelper dbHelper) {
   	 
        // 1. get reference to writable DB
        SQLiteDatabase db = dbHelper.getWritableDatabase();
 
        // 2. delete
        db.delete(this.getTableName(), //table name
                KEY_ID+" = ?",  // selections
                new String[] { String.valueOf(id) }); //selections args
 
        // 3. close
        db.close();
 
        //log
    Log.d("deleteTransactions", this.toString());
 
    }

	public String getTableName(){
		return TABLE_NAME;
	}

}
