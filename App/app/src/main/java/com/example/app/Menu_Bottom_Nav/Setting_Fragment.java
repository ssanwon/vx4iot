package com.example.app.Menu_Bottom_Nav;

import android.content.Intent;
import android.content.res.ColorStateList;
import android.graphics.Color;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.example.app.CurrentData;
import com.example.app.R;
import com.example.app.SettingData;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.Objects;

public class Setting_Fragment extends Fragment {

    private View fm_setting;
    private Button bt_update;
    private FloatingActionButton fab;
    private EditText tempSetting, tempDelta1, time, tempAlarm, tempDelta2;
    private final DatabaseReference mData = FirebaseDatabase.getInstance().getReference();

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        fm_setting = inflater.inflate(R.layout.fragment_setting, container, false);

        anhXa();

        updateEvent();

        FloatingButton();

        realtimeData();

        return fm_setting;
    }

    private void anhXa() {
        bt_update = fm_setting.findViewById(R.id.bt_update);
        fab = fm_setting.findViewById(R.id.fab);
        tempSetting = fm_setting.findViewById(R.id.tempSetting);
        tempDelta1 = fm_setting.findViewById(R.id.tempDelta1);
        time = fm_setting.findViewById(R.id.time);
        tempAlarm = fm_setting.findViewById(R.id.tempAlarm);
        tempDelta2 =fm_setting.findViewById(R.id.tempDelta2);
    }

    private void updateEvent() {
        bt_update.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                SettingData settingData = new SettingData(tempSetting.getText().toString(),
                        tempDelta1.getText().toString(), time.getText().toString(), tempAlarm.getText().toString(), tempDelta2.getText().toString());
                mData.child("Setting").setValue(settingData);
                Toast.makeText(getActivity(), "Cập nhật thành công", Toast.LENGTH_SHORT).show();
            }
        });
    }

    private void FloatingButton() {
        fab.setImageTintList(ColorStateList.valueOf(Color.WHITE));

        fab.setOnClickListener(v -> {
            Intent intent = new Intent(getActivity(), History_Activity.class);
            startActivity(intent);
        });
    }

    private void realtimeData() {
        mData.child("Setting").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                SettingData settingData = snapshot.getValue(SettingData.class);
                assert settingData != null;
                tempSetting.setText(settingData.temp);
                tempDelta1.setText(settingData.tempDelta1);
                time.setText(settingData.time);
                tempAlarm.setText(settingData.tempAlarm);
                tempDelta2.setText(settingData.tempDelta2);
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
    }
}