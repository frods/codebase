package com.cavaco.expensetracker;

import java.util.List;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.Spinner;

import com.cavaco.expensetracker.model.ModelBase;
import com.cavaco.expensetracker.model.Type;

public class Expense_trackerActivity extends Activity implements OnItemSelectedListener{
    /** Called when the activity is first created. */
	public static final String NEW_TYPE = "New Type...";
	
	private String[] array_spinner;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        SQLiteHelper dbHelper = new SQLiteHelper(this);
		
        Log.d("starting", "WOOOP");

        Type baseType = new Type();
        //Type food = new Type("Food", "Credit");
        //food.addToDb(dbHelper);
        
        List<ModelBase> types = baseType.getAllFromDb(dbHelper);
        
        array_spinner=new String[types.size() + 1];
        for (int i=0; i<types.size(); i++){
            Log.d("starting", "in loop");
        	ModelBase modelType = types.get(i);
            Log.d("starting", "got type");
        	if(modelType instanceof Type){
                Log.d("starting", "model is type");
        		Type type = (Type) modelType;
        		Log.d("starting", type.getName());        		
        		array_spinner[i] = type.getName();
        	}
        	else{
                Log.d("starting", "model not type");
        	}
        }
        array_spinner[types.size()]= NEW_TYPE;
        
        Spinner s = (Spinner) findViewById(R.id.transaction_type);
        ArrayAdapter adapter = new ArrayAdapter(this,
        		android.R.layout.simple_spinner_item, array_spinner);
        s.setAdapter(adapter);
        s.setOnItemSelectedListener(this);
    }
    
    /** Called when the user selects the Enter button */
    public void sendMessage(View view) {
        Intent intent = new Intent(this, DisplayMessageActivity.class);
        
        Spinner transaction_type = (Spinner) findViewById(R.id.transaction_type);
        String type = transaction_type.getSelectedItem().toString();
        intent.putExtra("Type", type);
        
        DatePicker date = (DatePicker) findViewById(R.id.date);
        int day = date.getDayOfMonth();
        int month = date.getMonth();
        int year = date.getYear();
        intent.putExtra("Day", day);
        intent.putExtra("Month", month);
        intent.putExtra("Year", year);
        
        EditText ammountText = (EditText) findViewById(R.id.ammount);
        float ammount = Float.valueOf(ammountText.getText().toString());
        intent.putExtra("ammount", ammount);
        
        EditText descriptionText = (EditText) findViewById(R.id.description);
        String description = descriptionText.getText().toString();
        intent.putExtra("description", description);
        startActivity(intent);
    }

	@Override
	public void onItemSelected(AdapterView<?> parent, View view, int position,
			long id) {
		// TODO Auto-generated method stub
		Log.d("typeSpinner", "Selected " + parent.getItemAtPosition(position));
		if(parent.getItemAtPosition(position) == NEW_TYPE){
			Log.d("typeSpinner", "create new type");
			
		}
		
	}

	@Override
	public void onNothingSelected(AdapterView<?> parent) {
		// TODO Auto-generated method stub
		
	}
    
    
}
