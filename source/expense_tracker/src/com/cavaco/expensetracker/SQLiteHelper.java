package com.cavaco.expensetracker;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import com.cavaco.expensetracker.model.Account;
import com.cavaco.expensetracker.model.Currency;
import com.cavaco.expensetracker.model.Transaction;
import com.cavaco.expensetracker.model.Type;
 
public class SQLiteHelper extends SQLiteOpenHelper {
 
    // Database Version
    private static final int DATABASE_VERSION = 1;
    // Database Name
    private static final String DATABASE_NAME = "BookDB";
 
    public SQLiteHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);  
    }
 
    @Override
    public void onCreate(SQLiteDatabase db) {
        // create books table
        db.execSQL(new Currency().getCreateTableString());
        db.execSQL(new Type().getCreateTableString());
        db.execSQL(new Account().getCreateTableString());
        db.execSQL(new Transaction().getCreateTableString());
    }
 
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        // Drop older tables if existed
        db.execSQL(new Transaction().getDropTableString());
        db.execSQL(new Account().getDropTableString());
        db.execSQL(new Type().getDropTableString());
        db.execSQL(new Currency().getDropTableString());
 
        // create fresh books table
        this.onCreate(db);
    }
 
}