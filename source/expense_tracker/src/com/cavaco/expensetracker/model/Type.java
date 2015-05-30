package com.cavaco.expensetracker.model;

import java.util.EnumSet;
import java.util.HashMap;
import java.util.Map;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.LinearLayout.LayoutParams;
import android.widget.PopupMenu;
import android.widget.PopupWindow;
import android.widget.RadioButton;
import android.widget.RadioGroup;

public class Type extends ModelBase{
	public enum TransactionType{
		CREDIT(0), DEBIT(1);
		public final int id;
		TransactionType(int id)
		{
			this.id = id;
		}
		private static final Map<Integer,TransactionType> lookup 
	      = new HashMap<Integer,TransactionType>();

		static {
			for(TransactionType s : EnumSet.allOf(TransactionType.class))
				lookup.put(s.id, s);
		}
	
		public static TransactionType get(int code) { 
			return lookup.get(code); 
		}
	}

	private int id;
	private String name;
	private TransactionType type;
	
	public static final String TABLE_NAME = "types";
	
    private static final String KEY_NAME = "name";
    private static final String KEY_TYPE = "type";
    
    public String getCreateTableString(){
    	return  "CREATE TABLE " + TABLE_NAME + " ( " +
    		KEY_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, " + 
            KEY_NAME + " TEXT UNIQUE NOT NULL, " +
    		KEY_TYPE + " INTEGER )";
    }
	
    public Type(){}
	
	public Type(String name, TransactionType type)
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
    	values.put(KEY_TYPE, type.id); 
    	return values;
	}

	@Override
	public void setFromCursor(Cursor cursor)
	{
        this.id = Integer.parseInt(cursor.getString(0));
        this.name = cursor.getString(1);
        this.type = TransactionType.get(Integer.parseInt(cursor.getString(2)));
	}
	
	@Override
	public String toString() {
	    return "Type [id=" + id + ", name=" + name + ", type=" + type + "]";
	}
	
	public static void newTypeModal(View targetView, final NewTypeFunction func){
		Log.d("Type", "display create popup");

		final EditText nameEntry = new EditText(targetView.getContext());
		final RadioGroup typeSelection = new RadioGroup(targetView.getContext());
		for(TransactionType s : EnumSet.allOf(TransactionType.class))
		{
			RadioButton newButton = new RadioButton(targetView.getContext());
			newButton.setText(s.toString());
			typeSelection.addView(newButton, s.id);
		}
		final PopupWindow popUp = new PopupWindow(targetView);
		
		Button createButton = new Button(targetView.getContext());
		createButton.setText("Create");
		createButton.setOnClickListener(new OnClickListener() {
			 public void onClick(View v) {
				 popUp.dismiss();
				 Type newType = new Type(nameEntry.getText().toString(), TransactionType.get(typeSelection.getCheckedRadioButtonId()));
				 func.function(newType);
            }			
		});
		LayoutParams params = new LayoutParams(LayoutParams.WRAP_CONTENT,
                LayoutParams.WRAP_CONTENT);
		LinearLayout layout = new LinearLayout(targetView.getContext());
        layout.setOrientation(LinearLayout.VERTICAL);
        layout.addView(nameEntry, params);
        layout.addView(typeSelection, params);
        layout.addView(createButton, params);
        popUp.setContentView(layout);

        popUp.showAtLocation(targetView, Gravity.CENTER_VERTICAL, 10, 10);
        popUp.setFocusable(true);
        popUp.update(50, 50, 300, 300);
        //popUp.showAsDropDown(targetView, xoff, yoff);
        //popUp.showAsDropDown(targetView);
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
		return type.toString();
	}

	public void setType(TransactionType type) {
		this.type = type;
	}

	public String getTableName(){
		return TABLE_NAME;
	}
}
