package com.example.birthday;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    // Load the native library
    static {
        System.loadLibrary("native-lib");
    }

    // Declare native methods
    private native String convertToBase64(String input);
    private native String convertFromBase64(String input);

    @SuppressLint("SetTextI18n")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // UI elements
        findViewById(R.id.birthdayCakeImage);
        EditText birthDateEditText = findViewById(R.id.birthDateEditText);
        TextView birthDateLabel = findViewById(R.id.birthDateLabel);
        Button convertButton = findViewById(R.id.convertButton);

        convertButton.setOnClickListener(v -> {
            String birthdate = birthDateEditText.getText().toString();
            String encoded = convertToBase64(birthdate);
            String decoded = convertFromBase64(encoded);
            birthDateLabel.setText("Original: " + birthdate + "\nEncoded: " + encoded + "\nDecoded: " + decoded);
        });
    }
}


