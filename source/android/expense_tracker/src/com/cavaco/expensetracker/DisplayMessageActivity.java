package com.cavaco.expensetracker;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.cavaco.expensetracker.model.Type;

public class DisplayMessageActivity extends Activity {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
 
        Intent intent = getIntent();
        String ammount = intent.getStringExtra("Ammount");
        String description = intent.getStringExtra("Note");
        
        TextView textView = new TextView(this);
        textView.setTextSize(40);
        textView.setText(ammount);
        
        setContentView(textView);
    }

}
